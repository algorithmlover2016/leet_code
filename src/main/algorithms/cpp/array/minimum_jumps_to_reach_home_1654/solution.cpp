#include "../../head.h"


class Solution {
public:
    int minimumJumps(std::vector<int> const & forbidden, int a, int b, int const x) {
        // plagiarizing idea from https://youtu.be/FZaUh9vVcKc
        // must record the status exactly

        std::unordered_set<int> forbiddenSet(forbidden.begin(), forbidden.end());

        std::set<std::pair<int, bool>> seen;
        std::queue<std::pair<int, bool>> curBfsQue;

        auto curPair = std::make_pair(0, false);
        curBfsQue.push(curPair);
        seen.insert(curPair);

        int ans = 0;
        while (!curBfsQue.empty()) {
            std::queue<std::pair<int, bool>> nextBfsQue;
            while (!curBfsQue.empty()) {
                auto const  [pos, canBack] = curBfsQue.front(); curBfsQue.pop();
                if (x == pos) {
                    return ans;
                }

                std::pair<int, bool> nextForwPair = std::make_pair(pos + a, true);
                if (forbiddenSet.find(nextForwPair.first) == forbiddenSet.end() &&
                    nextForwPair.first < MAX_FORWARD_FAR &&
                    seen.find(nextForwPair) == seen.end()) {
                    nextBfsQue.push(nextForwPair);
                    seen.insert(nextForwPair);
                }

                std::pair<int, bool> nextBackPair = std::make_pair(pos - b, false);
                if (canBack && JUST_ZERO <= nextBackPair.first &&
                    forbiddenSet.find(nextBackPair.first) == forbiddenSet.end() &&
                    seen.find(nextBackPair) == seen.end()) {
                    nextBfsQue.push(nextBackPair);
                    seen.insert(nextBackPair);
                }
            }
            ans++;
            std::swap(nextBfsQue, curBfsQue);
        }
        return -1;
    }
private:
    static int const JUST_ZERO = 0;
    static int const MAX_FORWARD_FAR = 50000;
};

class SolutionOptimizeSpace {
public:
    int minimumJumps(std::vector<int> const & forbidden, int a, int b, int const x) {
        // plagiarizing idea from https://youtu.be/FZaUh9vVcKc
        // must record the status exactly

        std::unordered_set<int> forbiddenSet(forbidden.begin(), forbidden.end());

        std::unordered_set<int> seen;
        std::queue<int> curBfsQue;

        int cur = (0 << SHIFT_LEFT);
        curBfsQue.push(cur);
        seen.insert(cur);

        int ans = 0;
        while (!curBfsQue.empty()) {
            std::queue<int> nextBfsQue;
            while (!curBfsQue.empty()) {
                int cur = curBfsQue.front(); curBfsQue.pop();
                int pos = cur >> SHIFT_LEFT;
                bool canBack = cur & 0x01;

                if (x == pos) {
                    return ans;
                }

                int nextForwPos = pos + a;
                int nextForwStatus = 1 + (nextForwPos << SHIFT_LEFT);
                if (forbiddenSet.find(nextForwPos) == forbiddenSet.end() &&
                    nextForwPos < MAX_FORWARD_FAR &&
                    seen.find(nextForwStatus) == seen.end()) {
                    nextBfsQue.push(nextForwStatus);
                    seen.insert(nextForwStatus);
                }

                int nextBackPos = pos - b;
                if (canBack && JUST_ZERO <= nextBackPos) {
                    int nextBackStatus = (nextBackPos << SHIFT_LEFT);
                    if (forbiddenSet.find(nextBackPos) == forbiddenSet.end() &&
                        seen.find(nextBackStatus) == seen.end()) {
                        nextBfsQue.push(nextBackStatus);
                        seen.insert(nextBackStatus);
                    }
                }
            }
            ans++;
            std::swap(nextBfsQue, curBfsQue);
        }
        return -1;
    }
private:
    static int const JUST_ZERO = 0;
    static int const MAX_FORWARD_FAR = 50000;
    static int const SHIFT_LEFT = 2;
};

class SolutionBetterTime {
public:
    int minimumJumps(std::vector<int> const & forb, int a, int b, int x) {
        // plagiarizing from better answer
        //unordered_set<int>seen;
        int m = 2001 + a + b;
        std::vector<bool> vis (m + 1,0);
        for(int i:forb) {
            vis[i] = true;
        }
        std::queue<std::pair<int, bool>> q;
        q.push({0, false});
        int dis = -1;
        vis[0] = true;
        while(!q.empty()) {
            dis++;
            int l = q.size();
            while (l--) {
                std::pair<int,int> f = q.front(); q.pop();
                //cout<<f.first<<" ";
                vis[f.first] = true;
                if(f.first == x) {
                    return dis;
                }

                int ff = f.first + a;
                int bb = f.first - b;
                if (ff <= m && !vis[ff]){
                    q.push({ff, true});
                    vis[ff] = true;
                }

                if(f.second) {
                    if(bb >= 0 && !vis[bb]){
                       // vis[bb] = true;
                        q.push({bb, false});
                    }
                }
            }
            //cout<<"\n";
        }
        return -1;
    }
};
