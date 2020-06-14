#include "../../head.h"


class SolutionTimeLimit {
public:
    std::vector<int> sortItems(int n, int m, std::vector<int> const & group, std::vector<std::vector<int>> const & beforeItems) {
        std::vector<std::vector<int>> groupMap(m + 1, std::vector<int>());
        std::unordered_map<int, std::set<int>> dependGraph;
        std::vector<int> degree(group.size(), 0);

        visited.resize(group.size(), false);
        tovisit.resize(group.size(), false);

        for (int index = 0; index < group.size(); index++) {
            int mapIndex= m - 1 - group[index]; //reverse the index, -1 -> m, 0 -> m - 1, 1 -> m -2,...
            groupMap[mapIndex].emplace_back(index);
        }
        for (int index = 0; index < beforeItems.size(); index++) {
            for (int di = 0; di < beforeItems[index].size(); di++) {
                if (group[index] == group[beforeItems[index][di]]) {
                    auto ret = dependGraph[beforeItems[index][di]].emplace(index);
                    if (ret.second) {
                        degree[index]++;
                    }
                /*
                } else if (-1 == group[beforeItems[index][di]]) {
                    int mapIndex = m - 1 - group[index];
                    for (int ele : groupMap[mapIndex]) {
                        auto ret = dependGraph[beforeItems[index][di]].emplace(ele);
                        if (ret.second) {
                            degree[ele]++;
                        }
                    }
                } else if (-1 == group[index]) {
                    int mapIndex = m - 1 - group[beforeItems[index][di]];
                    for (int ele : groupMap[mapIndex]) {
                        auto ret = dependGraph[ele].emplace(index);
                        if (ret.second) {
                            degree[index]++;
                        }
                    }
                */
                } else {
                    int mapIndex = m - 1 - group[beforeItems[index][di]];
                    int ith = m - 1 - group[index];
                    for (int ele : groupMap[mapIndex]) {
                        for (int iele : groupMap[ith]) {
                            auto ret = dependGraph[ele].emplace(iele);
                            if (ret.second) {
                                degree[iele]++;
                            }
                        }
                    }

                }
            }
        }

        /*
        for (auto & pair : dependGraph) {
            std::cout << "key: " << pair.first << "\t";
            for (auto depend : pair.second) {
                std::cout << " depended: " << depend << "\t";
            }
            std::cout << "\n";

        }
        */


        std::vector<int> ans;
        std::queue<int> todo;
        for (int groupIndex = 0; groupIndex < groupMap.size(); groupIndex++) {
            for (auto groupEle : groupMap[groupIndex]) {
                if (0 == degree[groupEle]) {
                    // std::cout << "index degree: " << groupEle << "\t" << degree[groupEle] << "\n";
                    todo.emplace(groupEle);
                }
            }
        }
        while (todo.size()) {
            int index = todo.front(); todo.pop();
            // std::cout << "compute index: " << index << "\n";
            if (!acyclicDFS(index, dependGraph, degree, ans)) {
                return {};
            }
            // std::cout << "\n";
        }
        return ans.size() == group.size() ? ans : std::vector<int>();
    }
    private:
    // DFS
    bool acyclicDFS(int ele,
                    std::unordered_map<int, std::set<int>> const & dependGraph,
                    std::vector<int> & degree,
                    std::vector<int> & ans) {
        if (tovisit[ele]) {
            return false;
        }
        if (visited[ele]) {
            return true;
        }

        tovisit[ele] = visited[ele] = true;
        ans.emplace_back(ele);
        // std::cout << ele << "\t";
        if (dependGraph.count(ele)) {
            for (auto const depend : dependGraph.at(ele)) {
                if (0 == --degree[depend] && !acyclicDFS(depend, dependGraph, degree, ans)) {
                    return false;
                }
            }
        }
        tovisit[ele] = false;
        return true;

    }
    std::vector<bool> visited;
    std::vector<bool> tovisit;
};

class Solution {
public:
    std::vector<int> sortItems(int n, int m, std::vector<int> const & group, std::vector<std::vector<int>> const & beforeItems) {//4:18
        //规律：indegree只计数多少不包括具体元素是谁;outdegree包括具体元素，所以他是个二位数组
        std::vector<std::vector<int>> outdegree(n+m);
        std::vector<int> indegree(n+m,0);
        for (int i = 0; i < group.size(); i++) {
            if (group[i] != -1) {
                outdegree[n + group[i]].push_back(i); //表明：n+group[i]二级节点是i的pre node;i是n+group[i]的其中一个outdegree
                indegree[i]++; //同样说明if(group[i]==0，then indegree[i]缺省为零
            }
        }
        for (int i = 0; i < beforeItems.size(); i++) {
            for (int e : beforeItems[i]) {
                int a = group[e] == -1 ? e : n + group[e];
                int b = group[i] == -1 ? i : n + group[i];
                if (a == b) {//same group,ingroup order
                    outdegree[e].push_back(i);
                    indegree[i]++;
                } else { //different group; outgroup order
                    outdegree[a].push_back(b);//等于e和i都加n
                    indegree[b]++;
                }
            }
        }
        std::vector<int> res;
        for (int val=0; val < n + m; val++) {
            if (indegree[val] == 0) {
                dfs(res, n, outdegree, indegree, val);
            }
        }
        return res.size() == n ? res : std::vector<int>();
    }
    void dfs(std::vector<int> & res, int n, std::vector<std::vector<int>> & outdegree, std::vector<int>& indegree,int val) {
        if (val < n) {
            res.push_back(val);
        }
        indegree[val] = -1;//marked visited
        for (auto j : outdegree[val]) {
            indegree[j]--;
            if (indegree[j] == 0) {
                dfs(res, n, outdegree, indegree, j);
            }
        }
    }
};
