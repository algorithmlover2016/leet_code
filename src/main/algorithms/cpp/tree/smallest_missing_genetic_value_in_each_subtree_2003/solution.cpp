#include "../../head.h"\n\n\n

class Solution {
public:
    std::vector<int> smallestMissingValueSubtree(std::vector<int> const & parents, std::vector<int> const & nums) {
        // plagiarizing from https://youtu.be/in_qO4nOsqA
        int pSize = parents.size();
        int numsSize = nums.size();
        if (pSize != numsSize || 0 == pSize) {
            return {};
        }
        std::vector<int> ans(pSize, MIN_NODE_VAL);

        int node2Minval = 0; // init the idx of minVal to 0
        int maxVal = nums[node2Minval]; // init maxVal to be the first element in nums
        for (int idx = node2Minval + 1; idx < numsSize; idx++) {
            if (nums[idx] > maxVal) {
                maxVal = nums[idx];
            } else if (nums[idx] < nums[node2Minval]) {
                node2Minval = idx;
            }
        }

        if (MIN_NODE_VAL < nums[node2Minval]) {
            return ans;
        }

        std::unordered_map<int, std::vector<int>> treeNodes;
        for (int idx = 0; idx < pSize; idx++) {
            treeNodes[parents[idx]].emplace_back(idx);
        }

        std::vector<bool> visited(maxVal + 2, false);

        int curNode = node2Minval;
        int curMinval = MIN_NODE_VAL;
        while (ROOT_PARENT != curNode) {
            bfs(curNode, treeNodes, visited);
            while (visited[curMinval]) {
                curMinval++;
            }
            ans[curNode] = curMinval;
            curNode = parents[curNode];
        }
        return ans;

    }
private:
    void bfs(int curNode, std::unordered_map<int, std::vector<int>> const & treeNodes, std::vector<bool> & visited) {
        if (!visited[curNode]) {
            visited[curNode] = true;
            for (int child : treeNodes.at(curNode)) {
                bfs(child, treeNodes, visited);
            }
        }
    }

private:
    static int const ROOT_PARENT = -1;
    int const MIN_NODE_VAL = 1;
};

class UF {
public:
	UF(int n) : parents(n, -1), ranks(n, 0) {
		for (int u = 0; u < n; ++u) {
			parents[u] = u;
		}
	}
	int find(int u) {
		if (parents[u] == u) {
			return u;
		}
		return parents[u] = find(parents[u]);
	}
	void merge(int u, int v) {
		int rootu = find(u);
		int rootv = find(v);
		if (rootu == rootv) {
			return;
		}
		if (ranks[rootu] > ranks[rootv]) {
			std::swap(rootu,rootv);
		}
		parents[rootu] = rootv;
		if (ranks[rootu] == ranks[rootv]) {
			ranks[rootv]++;
		}
	}
private:
	std::vector<int> parents;
	std::vector<int> ranks;
};

class Solution {
public:
	std::vector<int> smallestMissingValueSubtree(std::vector<int> const & parents, std::vector<int> const & nums) {
		int n = parents.size();
		std::vector<int> deg(n,0);
		std::vector<int> nodes(int(1e5)+2, -1);
		for (int v = 0; v < n; ++v) {
			nodes[nums[v]] = v;
			if (parents[v] >= 0) {
				deg[parents[v]]++;
			}
		}
		std::vector<int> curr;
		for (int v = 0; v < n; ++v) {
			if (deg[v] == 0) {
				curr.push_back(v);
			}
		}
		UF uf(n);
		std::vector<int> ans(n,0);
		int u = nodes[1];
		int x = 1;
		if (u >= 0) {
			while (!curr.empty()) {
				std::vector<int> next;
				for (int v : curr) {
					if (uf.find(v) != uf.find(u)) {
						ans[v] = 1;
						int p = parents[v];
						deg[p]--;
						if (deg[p] == 0) {
							next.push_back(p);
						}
						if (parents[v] >= 0) {
							uf.merge(v, parents[v]);
						}
					}
				}
				curr = next;
			}
			++x;
			while (x <= int(1e5)) {
				int v = nodes[x];
				if (v == -1) {
					break;
				}
				if (uf.find(v) != uf.find(u)) {
					ans[u] = x;
					uf.merge(u, parents[u]);
					u = parents[u];
				} else {
					++x;
				}
			}
		}
		for (int v = 0; v < n; ++v) {
			if (!ans[v]) {
				ans[v] = x;
			}
		}
		return ans;
	}
};
