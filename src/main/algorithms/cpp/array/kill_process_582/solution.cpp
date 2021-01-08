#include "../../head.h"

#define TEST
#define TEST_OUTPUT_TO_SCREEN

class Solution {
public:
    std::vector<int> killProcess(std::vector<int> const & pid,
            std::vector<int> const & ppid,
            int kill) {
        int const pidSize = pid.size();
        int const ppidSize = ppid.size();
        std::vector<int> ans;
        if (JUST_EMPTY == pidSize || pidSize != ppidSize) {
            return ans;
        }
        std::unordered_map<int, std::vector<int>> ppid2pid;
        for (int idx = 0; idx < ppidSize; idx++) {
            ppid2pid[ppid[idx]].emplace_back(pid[idx]);
        }
        std::queue<int> needKill;
        needKill.emplace(kill);
        while (!needKill.empty()) {
            int killId = needKill.front(); needKill.pop();
            ans.emplace_back(killId);
            // if (ppid2pid.find(killId) != ppid2pid.end()) { // there is no need to check this, because if
            // there is no key existing at ppid2pid, ppid2pid[killId] will be empty vector
            for (auto const cid : ppid2pid[killId]) {
                needKill.emplace(cid);
            }
            // }
        }
        return ans;
    }
private:
    static int const JUST_EMPTY = 0;
};

#ifdef TEST
int main() {
    Solution obj;
    std::vector<int> pid{{1, 3, 10, 5}},
                    ppid{{3, 0, 5, 3}};
    int kill(5);
#ifdef TEST_OUTPUT_TO_SCREEN
    std::cout << "\nTEST OUTPUT\n";
    for (auto const id : obj.killProcess(pid, ppid, kill)) {
        std::cout << id << ",\t";
    }
    std::cout << "\n";
#endif
}
#endif
