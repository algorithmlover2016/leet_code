#include "../../head.h"

class SolutionTimeLimit {
public:
    std::vector<int> findMinHeightTrees(int n, std::vector<std::vector<int>> const & edges) {
        std::vector<std::vector<int>> graph(n);
        std::vector<int> degree(n, 0);

        for (int i = 0; i < edges.size(); i++) {
            graph[edges[i][0]].emplace_back(edges[i][1]);
            graph[edges[i][1]].emplace_back(edges[i][0]);
            degree[edges[i][0]]++;
            degree[edges[i][1]]++;
        }

        std::vector<int> ans;
        int minHeight = INT_MAX;
        for (int index = 0; index < n; index++) {
            int target_index = -1;
            // int maxEdge = -1;
            // for (int s = 0; s < n; s++) {
            //     if (maxEdge < degree[s]) {
            //         maxEdge = degree[s];
            //         target_index = s;
            //     }
            // }
            // if (-1 == target_index) {
            //     break;
            // }
// 
            // degree[target_index] = 0;
            target_index = index;

            int height = 0;
            std::queue<int> todo;
            todo.emplace(target_index);
            std::vector<bool> visited(n, false);
            while(!todo.empty()) {
                int curFloorSize = todo.size();
                height++;
                for (int j = 0; j < curFloorSize; j++) {
                    int cur = todo.front(); todo.pop();
                    visited[cur] = true;
                    for (auto neighbor : graph[cur]) {
                        if (!visited[neighbor]) {
                            todo.emplace(neighbor);
                        }
                    }
                }
            }
            if (height < minHeight) {
                minHeight = height;
                // std::cout << "minHeight: " << minHeight << "\t" << "target_index: " << target_index << "\n";
                ans.clear();
                ans.emplace_back(target_index);
            } else if (height == minHeight) {
                // std::cout << "equal minHeight: " << minHeight << "\t" << "target_index: " << target_index << "\n";
                ans.emplace_back(target_index);
            }

        }
        return ans;
    }


}; 


class SolutionBFS {
public:

    struct Node {
        std::unordered_set<int> neighbor;

        inline bool isLeaf() const {
            return neighbor.size() == 1;
        }
    };

    std::vector<int> findMinHeightTrees(int n, std::vector<std::vector<int>> const & edges) {
        // plagiarizing from https://leetcode.com/problems/minimum-height-trees/discuss/76104/C%2B%2B-Solution.-O(n)-Time-O(n)-Space

        std::vector<int> buffer1;
        std::vector<int> buffer2;
        std::vector<int>* pB1 = &buffer1;
        std::vector<int>* pB2 = &buffer2;

        if(n == 1) {
            buffer1.push_back(0);
            return buffer1;
        }

        if(n==2) {
            buffer1.push_back(0);
            buffer1.push_back(1);
            return buffer1;
        }

        // build the graph
        std::vector<Node> nodes(n);
        for(auto const & p:edges) {
            if (p.size() < 2) {
                continue;
            }
            nodes[p[0]].neighbor.insert(p[1]);
            nodes[p[1]].neighbor.insert(p[0]);
        }

        // find all leaves
        for(int i=0; i<n; ++i) {
            if(nodes[i].isLeaf()) {
                pB1->push_back(i);
            }
        }

        // remove leaves layer-by-layer
        while(true) {
            for(int i : *pB1) {
                for(auto n: nodes[i].neighbor) {
                    nodes[n].neighbor.erase(i);
                    if(nodes[n].isLeaf()) {
                        pB2->push_back(n);
                    }
                }
            }

            if(pB2->empty()) {
                // the last layer
                return *pB1;
            }
            pB1->clear();
            std::swap(pB1, pB2);
        }
        return {};

    }
};

class SolutionDFS {
public:
    void dfs(vector<int> adj[],int v,int l,vector<bool>&vis,vector<int> &lvl,int &ans){
        vis[v]=true;
        lvl[v]=l;
        ans=max(ans,l);
        for(auto ch:adj[v]){
            if(!vis[ch])
                dfs(adj,ch,l+1,vis,lvl,ans);
        }
    }

    std::vector<int> findMinHeightTrees(int n, std::vector<std::vector<int>>& edges) {
        std::vector<int> res;
        if(n == 0)
            return res;
        std::vector<int> adj[n];

        for (int i = 0;i < edges.size(); i++) {
            adj[edges[i][0]].push_back(edges[i][1]);
            adj[edges[i][1]].push_back(edges[i][0]);
        }

        int deg[n];
        std::queue<int> q;
        for (int i = 0; i < n; i++) {
            deg[i] = adj[i].size();
            if (deg[i] == 1) {
                q.push(i);
            }
        }

        std::vector<int> lvl(n,0);
        int ans=0;
        while(!q.empty()){
            int v=q.front();
            q.pop();
            for (auto ch : adj[v]) {
                deg[ch]--;
                if (deg[ch] == 1) {
                    lvl[ch] = lvl[v] + 1;
                    ans = std::max(ans, lvl[ch]);
                    q.push(ch);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if(lvl[i]==ans){
                res.push_back(i);
            }
        }

        return res;
    }
};

class SolutionSmart {
public:
    std::vector<int> findMinHeightTrees(int n, std::vector<std::vector<int>>& edges) {
        if(n == 1) {
            return {0};
        }
        std::vector<int> nbcount(n, 0);
        std::vector<int> nbsum(n, 0);
        for (auto& v : edges) {
            nbcount[v[0]]++;
            nbcount[v[1]]++;
            nbsum[v[0]] += v[1];
            nbsum[v[1]] += v[0];
        }

        std::vector<int> next;
        for(int i = 0; i < n; i++) {
            if(nbcount[i] == 1) {
                next.push_back(i);
            }
        }

        int beg = 0, end = next.size();
        while (next.size() < n) {
            // the leaf layer
            for (int i = beg; i < end; i++) {
                // next[i] represent leaf
                // nbsum[next[i]] represent the leaf's parent
                int nb = nbsum[next[i]];
                nbcount[nb]--; // parent does not connect to this leaf
                nbsum[nb] -= next[i];
                if (nbcount[nb] == 1) {
                    // parent become new leaf
                    next.push_back(nb);
                }
            }
            // the next layer
            beg = end;
            end = next.size();
        }
        return std::vector<int>(next.begin() + beg, next.end());
    }
};
