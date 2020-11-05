#include "../../head.h"


class SolutionBackTracing {
public:
    int maximumRequests(int n, std::vector<std::vector<int>> const & requests) {
        // plagiarizing from https://www.youtube.com/watch?v=Rb9JFpunOAw
        int ans = 0;
        std::unordered_map<int, int> indegrees;
        backTracing(requests, indegrees, 0, 0, ans);
        return ans;
    }
    void backTracing(std::vector<std::vector<int>> const & requests,
            std::unordered_map<int, int> & indegrees,
            int index, int cnt, int & ans) {
        if (index >= requests.size()) {
            for (std::unordered_map<int, int>::iterator it = indegrees.begin();
                    it != indegrees.end(); it++) {
                if (0 != it->second) {
                    return;
                }
            }
            ans = std::max(ans, cnt);
            return;
        }

        int from = requests[index][0];
        int to = requests[index][1];
        indegrees[from] -= 1;
        indegrees[to] += 1;
        backTracing(requests, indegrees, index + 1, cnt + 1, ans);
        indegrees[from] += 1;
        indegrees[to] -= 1;
        backTracing(requests, indegrees, index + 1, cnt, ans);
    }
};

class SolutionBitMask {
public:
    int maximumRequests(int n, std::vector<std::vector<int>> const & requests) {
        int ans = 0;
        int requestsLen = requests.size();
        for (int mask = 1; mask < (1 << requestsLen); mask++) {
            std::vector<int> froms(n, 0);
            std::vector<int> tos(n, 0);

            int sum = 0;
            for (int index = 0; index < requestsLen; index++) {
                if ((1 << index) & mask) {
                    froms[requests[index][0]] += 1;
                    tos[requests[index][1]] += 1;
                    sum++;
                }
            }
            if (froms == tos) {
                // ans = std::max(ans, std::accumulate(froms.begin(), froms.end(), 0));
                ans = std::max(ans, sum);
            }
        }
        return ans;
    }
};
