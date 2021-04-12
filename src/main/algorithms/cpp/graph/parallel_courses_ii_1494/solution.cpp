#include "../../head.h"


#define DEBUG
class SolutionWANS {
public:
    int minNumberOfSemesters(int n, std::vector<std::vector<int>> const & dependencies, int k) {
        // construct the graph and then remove edges
        std::vector<std::set<int>> directedGraph(n + 1);
        std::vector<std::set<int>> reverseDependGraph(n + 1);
        for (auto const & dependency : dependencies) {
            if (DEPENDENCY_SIZE < dependency.size()) {
                continue;
            }
            directedGraph[dependency[DEPENDED_IDX]].insert(dependency[DEPENDING_IDX]);
            reverseDependGraph[dependency[DEPENDING_IDX]].insert(dependency[DEPENDED_IDX]);
        }
        std::vector<int> noDepended;
        // first find the no depended vertexes
        for (int idx = 1; idx < directedGraph.size(); idx++) {
            if (directedGraph[idx].empty()) {
                // there is an order if the idx is depended by others or not;
                // we should first pop element that is depended by others
                // ERROR AT HERE
                noDepended.emplace_back(idx);
                #ifdef DEBUG
                std::cout << idx << ", ";
                #endif
            }
        }
        #ifdef DEBUG
        std::cout << "\n";
        #endif
        int ans = 0;
        std::vector<int> visited;
        while (visited.size() < n) {
            int maxPop = k;
            #ifdef DEBUG
            std::cout << "\n" << ans << "\n";
            #endif
            std::vector<int> nextNoDepend;
            while (!noDepended.empty() && maxPop > 0) {
                int cur = noDepended.back(); noDepended.pop_back();
                maxPop--;
                #ifdef DEBUG
                std::cout << maxPop << ", " << cur << "; ";
                #endif

                visited.emplace_back(cur);
                for (auto const depended : reverseDependGraph[cur]) {
                    directedGraph[depended].erase(cur);
                    if (directedGraph[depended].empty()) {
                        nextNoDepend.emplace_back(depended);
                    }
                }
            }
            noDepended.insert(noDepended.end(), nextNoDepend.begin(), nextNoDepend.end());
            ans++;
        }
        return ans;
    }
private:
    static int const DEPENDENCY_SIZE = 2;
    static int const DEPENDING_IDX = 0;
    static int const DEPENDED_IDX = 1;
};

// #define DEBUG
class SolutionWrongAnsWithWrongOrder {
public:
    int minNumberOfSemesters(int n, std::vector<std::vector<int>> const & dependencies, int k) {
        // construct the graph and then remove edges
        std::vector<std::set<int>> directedGraph(n + 1);
        std::vector<std::set<int>> reverseDependGraph(n + 1);
        for (auto const & dependency : dependencies) {
            if (DEPENDENCY_SIZE < dependency.size()) {
                continue;
            }
            directedGraph[dependency[DEPENDED_IDX]].insert(dependency[DEPENDING_IDX]);
            reverseDependGraph[dependency[DEPENDING_IDX]].insert(dependency[DEPENDED_IDX]);
        }
        std::vector<int> order(n + 1, 0);
        int weight = 0;
        auto cmp = [&](int left, int right) {
            return (reverseDependGraph[left] < reverseDependGraph[right]) || (order[left] > order[right]);
        };
        typedef std::priority_queue<int, std::vector<int>, decltype(cmp)> MaxHeap;
        MaxHeap noDepended(cmp);
        // first find the no depended vertexes
        for (int idx = 1; idx < directedGraph.size(); idx++) {
            if (directedGraph[idx].empty()) {
                // there is an order if the idx is depended by others or not;
                // we should first pop element that is depended by others
                noDepended.emplace(idx);
                #ifdef DEBUG
                std::cout << idx << ", ";
                #endif
                order[idx] = weight++;
            }
        }
        #ifdef DEBUG
        std::cout << "\n";
        #endif
        int ans = 0;
        std::vector<int> visited;
        while (visited.size() < n) {
            int maxPop = k;
            #ifdef DEBUG
            std::cout << "\n" << ans << "\n";
            #endif
            std::vector<int> nextNoDepend;
            while (!noDepended.empty() && maxPop > 0) {
                int cur = noDepended.top(); noDepended.pop();
                maxPop--;
                #ifdef DEBUG
                std::cout << maxPop << ", " << cur << "; ";
                #endif

                visited.emplace_back(cur);
                for (auto const depended : reverseDependGraph[cur]) {
                    directedGraph[depended].erase(cur);
                    if (directedGraph[depended].empty()) {
                        nextNoDepend.emplace_back(depended);
                        order[depended] = weight++;
                    }
                }
            }
            for (auto const nextNode : nextNoDepend) {
                noDepended.emplace(nextNode);
            }
            ans++;
        }
        return ans;
    }
private:
    static int const DEPENDENCY_SIZE = 2;
    static int const DEPENDING_IDX = 0;
    static int const DEPENDED_IDX = 1;
};

class Solution {
public:
    int minNumberOfSemesters(int n, std::vector<std::vector<int>> const & dependencies, int k) {
        // plagiarizing idea from https://leetcode.com/problems/parallel-courses-ii/discuss/709382/C%2B%2B-O(3n)-bitmask-dynamic-programming-code-with-comments-and-tutorial
        std::vector<int> depen(n, 0);
        for (auto const & dependency : dependencies) {
            if (DEPENDENCY_SIZE > dependency.size()) {
                continue;
            }
            // make course start from 0 instead of 1
            int dependedCourse = dependency[DEPENDED_IDX] - 1;
            int dependingCourse = dependency[DEPENDING_IDX] - 1;
            depen[dependedCourse] |= (1 << dependingCourse);
        }

        int const MAX_STATUS_SIZE = (1 << n);
        std::vector<int> prerequests(MAX_STATUS_SIZE);
        for (int status = 0; status < MAX_STATUS_SIZE; status++) {
            for (int course = 0; course < n; course++) {
                if (status & (1 << course)) {
                    // if we want to take status course, we need depending course
                    prerequests[status] |= depen[course];
                }
            }
        }

        std::vector<int> dpMemo(MAX_STATUS_SIZE, n);
        dpMemo[0] = 0;
        for (int curStatus = 1; curStatus < MAX_STATUS_SIZE; curStatus++) {

            int alreadyTaken = curStatus ^ (MAX_STATUS_SIZE - 1);
            for (int subStatus = curStatus; subStatus != 0; subStatus = ((subStatus - 1) & curStatus)) {
                // from subStatus ^ curStatus to curStatus, we need subStatus
                // if the number of courses of subStatus is larger than k, we can't do status changing
                if (__builtin_popcount(subStatus) > k) {
                    continue;
                }
                if ((alreadyTaken & prerequests[subStatus]) == prerequests[subStatus]) {
                    // the depended course of subStatus representing has been taken
                    dpMemo[curStatus] = std::min(dpMemo[curStatus], dpMemo[curStatus ^ subStatus] + 1);
                }
            }
        }
        return dpMemo[MAX_STATUS_SIZE - 1];
    }
private:
    static int const DEPENDENCY_SIZE = 2;
    static int const DEPENDING_IDX = 0;
    static int const DEPENDED_IDX = 1;
};

// #define DEBUGGG
namespace { // alvin-777
#ifdef DEBUGGG
#define LOG(x) std::cout << (x) << std::endl << std::flush
#define PL(l) { std::cout << "["; for (auto & e : l) std::cout << e << ','; std::cout << "]" << std::endl; }
#else
#define LOG(x)
#define PL(l)
#endif
static auto _speedupMagic = [] { ios::sync_with_stdio(false); cin.tie(nullptr); return 0; }();
}

class Solution {
public:
    int minNumberOfSemesters(int n, std::vector<std::vector<int>> const & dependencies, int k) {
        std::array<std::pair<int, int>, 16> deps{};
        // availAll the first n bits are 1, the last bit will be 0, it is like 111...10 (n + 1 bits)
        int availAll = (1 << (n + 1)) - 2, availNow = availAll;
        for (auto & dep : dependencies) {
            deps[dep[0]].second |= 1 << dep[1];
            deps[dep[1]].first |= 1 << dep[0];
            // no depended bits will keep set
            availNow &= ~(1 << dep[1]);
        }
        std::array<int, 1 << 16> memo{};
        std::function<int(int, int)> BT = [&] (int aa, int an) -> int {
            if (!an) {
                // we can't take a course
                return 0;
            }
            if (memo[aa]) {
                // we have already compute the state
                return memo[aa];
            }
            int kk = std::min(k, __builtin_popcount(an));
            int sub = an, end = 0;
            while (__builtin_popcount(sub) > kk) {
                // remove the least significant 1 bit
                // keep the bit from left to right with at most kk bits;
                sub &= sub - 1;
            }
            for (int sh = 0; __builtin_popcount(end) < kk; ++sh) {
                // remove the most significant bits
                // keep the bits from right to left with at most kk bits
                end |= an & (1 << sh);
            }
            /*
               if kk == __builtin_popcount(an), sub == end;
               if kk > __builtin_popcount(an); sub > end;
             */
            int r = n;
            for (; sub >= end; sub = (sub - 1) & an) {
                // count the number of bits of sub to get the course that need taken
                int subbits = __builtin_popcount(sub);
                while (subbits > kk) {
                    // if the number is larget than k, we first deal with the most left k bits
                    sub &= sub - 1, --subbits;
                }
                if (subbits < kk) {
                    // because kk is std::min(k, __builtin_popcount(an)), subbits < kk is some cases, not all case
                    continue;
                }
                int aaNext = aa ^ sub, next = 0;
                for (int i = 1; i <= n; ++i) {
                    // the i idx need deal with and its depended courses are not in aaNext
                    // which means the i idx is free depended now
                    if (((1 << i) & aaNext) && !(deps[i].first & aaNext)) {
                        next |= 1 << i;
                    }
                }
                r = std::min(r, BT(aaNext, next) + 1);
                if (aa == availAll && r == (n + k - 1) / k) {
                    // n eleements and each time take k elements, it at least need (n + k - 1) / k times;
                    return memo[aa] = r;
                }
            }
            return memo[aa] = r;
        };
        return BT(availAll, availNow);
    }
};

class Solution {
private:
    int solve(int mask, std::vector<int> & dp, std::vector<std::vector<int>> & adj, int & n, int & k) {
        if( mask== ((1 << n) - 1)) {
            // All courses are taken
            return 0;
        }
        if(dp[mask] != -1) {
            // memoization
            return dp[mask];
        }

        std::vector<int> indeg(n,0);
        for(int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                continue;
            }
            for(auto it: adj[i]) {
                indeg[it]++;
            }
        }
        int temp=0;  // For a mask of all nodes with 0-indegree
        for (int i = 0; i < n; i++) {
            if (indeg[i] == 0 && !(mask & (1 << i))) {
                temp = temp | ( 1 << i);
            }
        }
        int j = temp;
        int cnt = __builtin_popcount(j);  // count of nodes with 0-indegree

        int ans = n + 1;  // ans will be 'n' in the worst case, so take (n+1) as infinity
        if (cnt > k) {
            for ( ; j; j = (j - 1) & temp) {
                // iterate through all submasks of temp
                cnt=__builtin_popcount(j);
                if (cnt != k) {
                    continue;
                }
                ans = std::min(ans, 1 + solve(mask | j, dp, adj, n, k));
            }
        } else {
            ans = std::min(ans, 1 + solve(mask | j, dp, adj, n, k));
        }
        return dp[mask] = ans;
    }

public:
    int minNumberOfSemesters(int n, std::vector<std::vector<int>> const & d, int k) {
        std::vector<int> dp(1 << n, -1);
        std::vector<std::vector<int>> adj(n);
        for (int i=0; i<d.size(); i++) {
            d[i][0]--;
            d[i][1]--;
            adj[d[i][0]].push_back(d[i][1]);
        }
        return solve(0, dp, adj, n, k);
    }
};
