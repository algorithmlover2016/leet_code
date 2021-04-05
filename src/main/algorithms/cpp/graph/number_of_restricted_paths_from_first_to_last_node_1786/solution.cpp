#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int countRestrictedPaths(int n, std::vector<std::vector<int>> const & edges) {
        // plagiarizing from https://youtu.be/YmufKoAmthE

        std::vector<std::vector<std::pair<int, int>>> graph(n + 1);
        for (auto const & edge : edges) {
            if (EDGE_SIZE > edge.size()) {
                continue;
            }
            graph[edge[FIRST_NODE_IDX]].emplace_back(std::make_pair(edge[SECOND_NODE_IDX], edge[EDGE_WEIGHT_IDX]));
            graph[edge[SECOND_NODE_IDX]].emplace_back(std::make_pair(edge[FIRST_NODE_IDX], edge[EDGE_WEIGHT_IDX]));
        }
        std::vector<int> shortestDist(n + 1, INT_MAX);
        // start from n node
        shortestDist[n] = 0;

        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> minHeap;
        // start from n node to the most weight node
        minHeap.emplace(std::make_pair(0, n));


        // find the shortest path for each node
        while (!minHeap.empty()) {
            auto const & ele = minHeap.top();
            int curShortestPath = ele.first;
            int curNode = ele.second;
            #ifdef DEBUG
            std::cout << curNode << ", " << curShortestPath << "\t";
            #endif
            minHeap.pop();
            for (auto const & neightbourWei : graph[curNode]) {
                int neiNode = neightbourWei.first;
                int edgeWei = neightbourWei.second;
                int nextWei = curShortestPath + edgeWei;
                if (shortestDist[neiNode] > nextWei) {
                    shortestDist[neiNode] = nextWei;
                    minHeap.emplace(std::make_pair(nextWei, neiNode));
                }
            }
        }

        std::vector<int> dpMemo(n + 1, INIT_FLAG);
        int ans = dfs(1, n, dpMemo, shortestDist, graph);
        return ans;
    }
    private:
    int dfs(int curNode, int endNode, std::vector<int> & dpMemo,
            std::vector<int> const & shortestDist, std::vector<std::vector<std::pair<int, int>>> const & graph) {
        if (curNode == endNode) {
            return 1;
        }

        if (INIT_FLAG != dpMemo[curNode]) {
            return dpMemo[curNode];
        }

        int ans = 0;
        for (auto const & edge : graph[curNode]) {
            int nextNode = edge.first;
            if (shortestDist[nextNode] < shortestDist[curNode]) {
                ans += dfs(nextNode, endNode, dpMemo, shortestDist, graph);
                ans %= MOD;
            }
        }
        return dpMemo[curNode] = ans;
    }
    private:
    static int const MOD = 1e9 + 7;
    int const INIT_FLAG = -1;
    static int const EDGE_SIZE = 3;
    static int const FIRST_NODE_IDX = 0;
    static int const SECOND_NODE_IDX = 1;
    static int const EDGE_WEIGHT_IDX = 2;
};


#define DEBUG
typedef unsigned int uint;
const int N = 20005, P = 1000000007, inf = ~0u>>1;
std::vector<std::pair<int,int> > e[N];
std::vector<int> seq;
int ans[N];
template<class T>
struct radix_heap{
	static const int W = 32;
    std::vector<std::pair<uint,T>> c[W + 1];
	int d[N], n; uint last;

	radix_heap():last(0) {
    }
	int getbit(int x) {
        return x ? 32 - __builtin_clz(x) : 0;
    }
	void push(uint k, const T & v) {
        c[getbit(k ^ last)].emplace_back(k,v);
    }
    std::pair<uint, T> pop() {
		while (c[0].empty()) {
			int i = 1;
            while (i <= W && c[i].empty()) {
                ++i;
            }
			if (i > W) {
                return std::make_pair(0,-1);
            }
			last = std::min_element(std::begin(c[i]), end(c[i]))->first;
			for (auto & p : c[i]) {
				if (p.first == d[p.second]) {
                    push(p.first, p.second);
                }
            }
			c[i].clear();
		}
        std::pair<uint,T> res=c[0].back(); c[0].pop_back();
		return res;
	}
	void SSSP(int S) {
		for (int i = 1; i <= n; ++i) {
            d[i] = inf;
        }
        d[S] = 0;
        push(0, S);
		while (1) {
            std::pair<uint,T> p = pop();
            uint d0 = p.first;
            int x = p.second;
			if (x == -1) {
                return;
            }
			if (d0 > d[x]) {
                continue;
            }
			seq.push_back(x);
			for (auto & ed : e[x]) {
				int y = ed.first, cost = ed.second;
				if (d0 + cost < d[y]) {
                    d[y] = d0 + cost, push(d[y], y);
                }
			}
		}
	}
};

class Solution {
public:
	int countRestrictedPaths(int n, std::vector<std::vector<int>> const & edges) {
		radix_heap<int> H;
        H.n=n;

		for (int i = 1; i <= n; ++i) {
            e[i].clear();
        }

        // init each one to zero, except the start node(n);
		for (int i = 1; i <= n; ++i) {
            ans[i] = 0;
        }
        ans[n] = 1;

		for (auto ed : edges) {
            e[ed[0]].emplace_back(ed[1], ed[2]), e[ed[1]].emplace_back(ed[0], ed[2]);
        }

		seq.clear(); H.SSSP(n);
		for (int x: seq) {
            #ifdef DEBUG
            std::cout << x << ", " << H.d[x] << "; ";
            #endif

			for (auto & ed : e[x]) {
				int y = ed.first;
                #ifdef DEBUG
                std::cout << y << ", " << H.d[y] << "; ";
                #endif
				if (H.d[y] < H.d[x]) {
                    ans[x] = (ans[x] + ans[y]) % P;
                }
			}
            #ifdef DEBUG
            std::cout << ans[x] << "\n";
            #endif
        }
		return ans[1];
	}
};

int _IO = [] () {
    ios::sync_with_stdio(0);
    cin.tie(0); //cout.tie(0);
    return 0;
}();
