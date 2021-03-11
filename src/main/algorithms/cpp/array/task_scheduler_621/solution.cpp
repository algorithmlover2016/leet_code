#include "../../head.h"


class Solution {
public:
    int leastInterval(std::vector<char> const & tasks, int n) {
        int const tasksSize = tasks.size();
        std::unordered_map<char, int> tasksCnt;
        int maxCnt = 0;
        for (auto const task : tasks) {
            if (++tasksCnt[task] > maxCnt) {
                maxCnt = tasksCnt[task];
            }
        }
        std::vector<char> maxCntTask;
        for (auto const & [task, cnt] : tasksCnt) {
            if (cnt == maxCnt) {
                maxCntTask.emplace_back(task);
            }
        }
        int curMax = maxCnt * (n + 1) - (n + 1 - maxCntTask.size());
        return std::max(curMax, tasksSize);
    }
};

class Solution {

public:
    int leastInterval(std::vector<char> const & tasks, int n) {
        int N = tasks.size(), maxi = 0, cnt[26]={0};
        for (char c : tasks) {
            cnt[c-'A']++;
            maxi = std::max(maxi, cnt[c-'A']);
        }
        int ans = (maxi-1) * (n+1);
        for (int i = 0; i < 26; i++) {
            if (cnt[i] == maxi) {
                ans++;
            }
        }
        return std::max(ans,N);
    }
};
