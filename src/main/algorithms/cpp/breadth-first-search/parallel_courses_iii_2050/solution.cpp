#include "../../head.h"


class Solution {
public:
    int minimumTime(int n, std::vector<std::vector<int>> const & relations, std::vector<int> const & time) {
        // plagiarizing from https://leetcode.com/problems/parallel-courses-iii/discuss/1537473/Python-short-dp-4-lines-explained
        std::vector<std::vector<int>> graph(n + 1);
        std::vector<int> degree(n + 1, 0);
        for (auto const & relation : relations) {
            assert(RELATION_SIZE <= relation.size());
            int lastIdx = relation.size() - 1;
            for (int idx = 0; idx < lastIdx; idx++) {
                graph[relation[lastIdx]].emplace_back(relation[idx]);
                degree[relation[lastIdx]]++;
            }
        }

        std::vector<int> dpMemo(n + 1, 0);
        int ans = INT_MIN;
        for (int idx = 0; idx < n; idx++) {
            ans = std::max(ans, dfs(idx + 1, dpMemo, time, graph));
        }
        return ans;
    }
private:
    int dfs(int idx, std::vector<int> & dpMemo, std::vector<int> const & time, std::vector<std::vector<int>> const & graph) {
        if (0 < dpMemo[idx]) {
            return dpMemo[idx];
        }
        int ans = 0;
        for (int pre : graph[idx]) {
            ans = std::max(ans, dfs(pre, dpMemo, time, graph));
        }
        ans += time[idx - 1];
        return dpMemo[idx] = ans;
    }

private:
    static int const RELATION_SIZE = 2;
};

// #define DEBUG
class Solution {
public:
    int minimumTime(int n, std::vector<std::vector<int>> const & relations, std::vector<int> const & time) {
        // plagiarizing from https://leetcode.com/problems/parallel-courses-iii/discuss/1537500/Track-Lead-Time and
        // https://leetcode.com/problems/parallel-courses-iii/discuss/1537479/C%2B%2BPython-Topology-Sort-O(M%2B-N)-Clean-and-Concise
        int const MOST_RIGHT_EXCLUDE = n + 1;
        std::vector<std::vector<int>> graph(MOST_RIGHT_EXCLUDE);
        std::vector<int> degree(MOST_RIGHT_EXCLUDE, 0);
        for (auto const & relation : relations) {
            assert(RELATION_SIZE <= relation.size());
            int lastIdx = relation.size() - 1;
            for (int idx = 0; idx < lastIdx; idx++) {
                graph[relation[idx]].emplace_back(relation[lastIdx]);
                degree[relation[lastIdx]]++;
            }
        }
        #ifdef DEBUG
        std::cout << "get graph and degree\n";
        #endif
        std::vector<int> zeroDegree;
        for (int idx = 1; idx < MOST_RIGHT_EXCLUDE; idx++) {
            if (ZERO_DEGREE == degree[idx]) {
                zeroDegree.emplace_back(idx);
            }
        }
        #ifdef DEBUG
        std::cout << "get zeroDegree\n";
        #endif
        std::vector<int> leads(MOST_RIGHT_EXCLUDE, 0);
        while (!zeroDegree.empty()) {
            std::vector<int> nextZeroDegree;
            for (int idx : zeroDegree) {
                leads[idx] += time[idx - 1];
                for (int next : graph[idx]) {
                    leads[next] = std::max(leads[idx], leads[next]);
                    if (ZERO_DEGREE == --degree[next]) {
                        nextZeroDegree.emplace_back(next);
                    }
                }
            }
            std::swap(zeroDegree, nextZeroDegree);
        }
        return *std::max_element(std::begin(leads), std::end(leads));
    }

private:
    static int const RELATION_SIZE = 2;
    static int const ZERO_DEGREE = 0;
};

class Solution {
public:
    int minimumTime(int n, std::vector<std::vector<int>> const & relations, std::vector<int> const & time) {
        std::vector<std::vector<int>> graph(n + 1);
        std::vector<int> timeStamp(n+1, 0), incoming(n+1, 0);
        for(std::vector<int> const & e : relations) {
            graph[e[0]].push_back(e[1]);
            incoming[e[1]]++;
        }
        
        std::queue<int> bfs;
        
        for(int i = 1; i <= n; i++) {
            if(incoming[i] == 0) {
                bfs.push(i);
            }
        }
        
        while(!bfs.empty()) {
            int qSize = bfs.size();
            while(qSize > 0) {
                qSize = qSize - 1;
                int node = bfs.front(); bfs.pop();
                int curNodeTimeStamp = timeStamp[node] + time[node - 1];
                for(int & v : graph[node]) {
                    timeStamp[v] = std::max(timeStamp[v], curNodeTimeStamp);
                    if(--incoming[v] == 0) {
                        bfs.push(v);
                    }
                }
            }
        }
        
        int totalTime = 0;
        for(int i = 1; i <= n; i++) {
            totalTime = std::max(totalTime, timeStamp[i]+time[i-1]);
        }
        return totalTime;
    }
};