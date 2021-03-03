#include "../../head.h"

// plagiarizing from https://blog.csdn.net/qq_40160605/article/details/80642518
#define DEBUG

#define TEST_MAIN
class Solution {
protected:
    friend struct Edge;
    struct Edge {
        int from;
        int to;
        int next;
        int w;
        Edge(int from_, int to_, int next_, int w_ = 1) : from(from_), to(to_), next(next_), w(w_) {
        }
        Edge() :
            from(Solution::LINKED__MOAST_LEFT_FLAG),
            to(Solution::LINKED__MOAST_LEFT_FLAG),
            next(Solution::LINKED__MOAST_LEFT_FLAG), w(0) {
        }
    };
public:
    Solution () : totEdge(0) {
        // using for linked forward list
        heads = std::vector<int>(MAX_NODES, LINKED_MOAST_LEFT_FLAG);
        edges = std::vector<struct Edge>(MAX_NODES * 2);

        // using for construct a tree
        parents = std::vector<std::vector<int>>(MAX_NODES, std::vector<int>(DEG, 0));
        gw = std::vector<std::vector<int>>(MAX_NODES, std::vector<int>(DEG, 0));

        // record the degree of each node
        deg = std::vector<int>(MAX_NODES);

        idx2Name = std::vector<std::string>(MAX_NODES);
        idx2Name[0] = "-1";

        childFlag = std::vector<bool>(MAX_NODES, false);

    }

    std::vector<std::string> query() {
        std::vector<std::string> ans;
        int records = 0;
        std::cin >> records;
        int u = 0, v = 0, w = 0;
        char parent[MAX_LEN], child[MAX_LEN];

        for (int idx = 1; idx <= records; idx++) {
            std::scanf("%s%s", parent, child);
            std::string uStr(parent);
            std::string vStr(child);
#ifdef DEBUG_SUC
            std::cout << __func__ << ", " << __LINE__ << "input: " << uStr << "\t" << vStr << "\n";
#endif
            u = name2Idx[uStr];
            v = name2Idx[vStr]; 
            if (DUMMY_ROOT == u || DUMMY_ROOT == v) {
                if (uStr == vStr) {
                    ans.emplace_back(uStr);
                } else {
                    ans.emplace_back(idx2Name[u]);
                }
                continue;
            }

            int sumPath = 0;
            int root = lca(u, v, sumPath);
#ifdef DEBUG
            std::cout << __func__ << ", " << __LINE__ << idx2Name[u] << ",\t" << idx2Name[v] << "\t"
                << "u, v: " << u << ",\t" << v << ",\t" << root << ",\t" << sumPath << "\n";
#endif
            ans.emplace_back(idx2Name[root]);
        }
        return ans;
    }

    void getInput() {
        int topNode = 1;
        int records = 0;
        std::cin >> records;
        int u = 0, v = 0, w = 0;
        char parent[MAX_LEN], child[MAX_LEN];

        for (int idx = 1; idx <= records; idx++) {
            std::scanf("%s%s", parent, child);
            std::string uStr(parent);
            if (name2Idx.find(uStr) == name2Idx.end()) {
                u = topNode++;
                name2Idx[uStr] = u;
                idx2Name[u] = uStr;
            } else {
                u = name2Idx[uStr];
            }

            std::string vStr(child);
            if (name2Idx.find(vStr) == name2Idx.end()) {
                v = topNode++;
                name2Idx[vStr] = v;
                idx2Name[v] = vStr;
            } else {
                v = name2Idx[vStr];
            }

            addEdge(u, v, 1);
            addEdge(v, u, 1);

            // mark the children nodes
            childFlag[v] = true;
        }

        for (int idx = 1; idx <= records; idx++) {
            if (!childFlag[idx]) {
                // idx is not a child node
                bfs(idx);
            }
        }
    }

    int lca(int u, int v, int & sumPath) {
        if (u >= MAX_NODES || v >= MAX_NODES) {
            return 0;
        }
        if (deg[u] > deg[v]) {
            std::swap(u, v);
        }
        int uDeg = deg[u], vDeg = deg[v];
        int curU = u, curV = v;
        for (int delta = vDeg - uDeg, idx = 0; delta; delta >>= 1, idx++) {
            if (delta & 0x01) {
                sumPath += gw[curV][idx];
#ifdef DEBUG
                std::cout << "upJump one: " << idx2Name[curV] << '\t';
#endif
                curV = parents[curV][idx];
            }
        }
        if (curV == curU) {
            return curU;
        }
        for (int idx = DEG - 1; idx > EXCLUDE_MOST_LEFT_IDX; idx--) {
            if (parents[curU][idx] == parents[curV][idx]) {
                // up jump too much
                continue;
            }

            sumPath += gw[curU][idx];
            curU = parents[curU][idx];

            sumPath += gw[curV][idx];
            curV = parents[curV][idx];

#ifdef DEBUG
                std::cout << "upJump two: " << idx2Name[curU] << '\t' << idx2Name[curV] << '\t';
#endif

        }

#ifdef DEBUG
        std::cout << "\n";
#endif

        sumPath += gw[curU][0] + gw[curV][0];
        return parents[curU][0]; 
    }

private:
    void bfs(int root) {
        std::queue<int> que;
        // there maybe many subTrees who are not connected.
        // so we construct a dummy node (which is -1) to as a dummy root
        que.emplace(root);
        parents[root][0] = DUMMY_ROOT; // all the root are connected to a dummy root
        gw[root][0] = 0; // the weight from root to dummy root is zero
        deg[root] = 1; // because we construct a dummy root node
        while (!que.empty()) {
            int tmpNode = que.front(); que.pop();
            for (int degIdx = 1; degIdx < DEG; degIdx++) {
                parents[tmpNode][degIdx] = parents[parents[tmpNode][degIdx - 1]][degIdx - 1];
                gw[tmpNode][degIdx] = gw[tmpNode][degIdx - 1] + gw[parents[tmpNode][degIdx - 1]][degIdx - 1];
            }
            for (int edgeIdx = heads[tmpNode]; edgeIdx != LINKED_MOAST_LEFT_FLAG; edgeIdx = edges[edgeIdx].next) {
                int v = edges[edgeIdx].to;
                if (v == parents[tmpNode][0]) {
                    // meeting its directly parent
                    // because we do twice operation when input a pair
                    continue;
                }
                deg[v] = deg[tmpNode] + 1;
                parents[v][0] = tmpNode;
                gw[v][0] = edges[edgeIdx].w;
                que.emplace(v);
            }
        }
    }

    void addEdge(int from, int to, int w) {
        edges[totEdge].from = from;
        edges[totEdge].to = to;
        edges[totEdge].w = w;
        edges[totEdge].next = heads[from];
        heads[from] = totEdge++;
    }


private:
    static int const EXCLUDE_MOST_LEFT_IDX = -1;
    static int const LINKED__MOAST_LEFT_FLAG = -1;
    int const LINKED_MOAST_LEFT_FLAG = LINKED__MOAST_LEFT_FLAG;
    static int const MAX_LEN = 1000;
    static int const DUMMY_ROOT = 0; // so topNode starts from 1. 0 is a dummy root
    int const MAX_NODES = 10010;
    int const DEG = 20;

    // using for linked forward list
    std::vector<int> heads;
    std::vector<struct Edge> edges;

    // using for construct a tree
    std::vector<std::vector<int>> parents;
    std::vector<std::vector<int>> gw;

    // record the degree of each node
    std::vector<int> deg;

    // record the map relationship of string and number
    std::unordered_map<std::string, int> name2Idx;
    std::vector<std::string> idx2Name;

    std::vector<bool> childFlag;

    int totEdge;
};

#ifdef TEST_MAIN
#define PRINT_TO_SCREEN
int main() {
    Solution obj;
    obj.getInput();
    std::vector<std::string> ans = obj.query();
#ifdef PRINT_TO_SCREEN
    std::cout << ans.size() << "\n";
    for (auto const & ele : ans) {
        std::cout << ele << "\n";
    }
    std::cout << std::endl;
#endif
}
#endif
