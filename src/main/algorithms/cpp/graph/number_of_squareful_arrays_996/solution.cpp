#include "../../head.h"
 

class SolutionConstructGraphDFS {
public:
    int numSquarefulPerms(std::vector<int> const & A) {
        // plagiarizing from https://leetcode.com/problems/number-of-squareful-arrays/discuss/238562/C%2B%2BPython-Backtracking
        if (A.empty()) {
            return 0;
        }
        for (auto ele : A) {
            cnt[ele]++;
        }
        for (auto const & pair : cnt) {
            for (auto const & subPair : cnt) {
                int x = pair.first;
                int y = subPair.first;
                int root = std::sqrt(x + y);
                if (root * root == x + y) {
                    pairGraph[x].emplace(y); // there is repeating computing, so there is no need to map y->x
                }
            }
        }
        // permunations
        int ans = 0;
        for (auto const & pair : cnt) {
            dfs(pair.first, pairGraph, A.size() - 1, ans);
        }
        return ans;
    }

    void dfs(int ele, int left, int & ans) {
        cnt[ele]--;
        if (0 == left) {
            ans++;
        } else {
            for (auto const ep : pairGraph[ele]) {
                if (cnt[ep] > 0) {
                    dfs(ep, left - 1, ans);
                }
            }
        }
        cnt[ele]++;
    }

private:
    std::unordered_map<int, int> cnt;
    std::unordered_map<int, std::unordered_set<int>> pairGraph;
};

class SolutionBetterRunTime {
public:
    int numSquarefulPerms(std::vector<int> const & A) {
        std::unordered_map<int, int> cnt;
        for(auto n : A) {
            ++cnt[n];
        }
        std::unordered_map<int, std::unordered_set<int>> edge;
        for(auto p1 : cnt) {
            int n1 = p1.first;
            for(auto p2 : cnt) {
                int n2 = p2.first;
                int n3 = sqrt((double)n1 + n2);
                if( (long long)n3 * n3 == (long long)n1 + n2 ) {
                    edge[n1].insert(n2);
                    // edge[n2].insert(n1); // there is no need to do
                }
            }
        }
        int rv = 0;
        function<void( int, int )> dfs = [&]( int len, int n ) {
            if( len == A.size() ) {
                ++rv;
                return;
            }

            --cnt[n];
            for( auto m : edge[n] ) {
                if( cnt[m] == 0 ) continue;
                dfs( len + 1, m );
            }
            ++cnt[n];
        };
        for( auto p : cnt ) {
            dfs(1, p.first);
        }
        return rv;
    }
};
