#include "../../head.h"

#define TEST_MAIN
#define RMQ_DEBUG
class Rmq {
public:
    Rmq(std::vector<int> const & nums, bool returnMin_ = true) : returnMin(returnMin_) {
        int const numsSize = nums.size();
        int maxLogSize = noLargeMaxExp(numsSize) + 1;
        dpFLog.resize(numsSize, std::vector<int>(maxLogSize, INIT_FLAG));

#ifdef RMQ_DEBUG
        std::cout << "RMQ_DEBUG: " << dpFLog.size() << ",\t" << dpFLog.back().size() << "\n";
#endif

        for (int idx = 0; idx < numsSize; idx++) {
            dpFLog[idx][0] = nums[idx];
        }

        for (int exp = 1; exp < maxLogSize; exp++) {
            int expVal = (1 << exp) - 1;
            for (int idx = 0; idx + expVal < numsSize; idx++) {
                if (returnMin) {
                            // from idx to idx + 2 ^ (exp - 1) - 1 total 2 ^ (exp - 1)
                    dpFLog[idx][exp] = std::min(dpFLog[idx][exp - 1],
                         // from idx + 2 ^ (exp - 1) to idx + 2 ^ (exp - 1) + 2 ^ (exp - 1) - 1
                            dpFLog[idx + (1 << (exp - 1))][exp - 1]);
                } else {
                    dpFLog[idx][exp] = std::max(dpFLog[idx][exp - 1],
                            dpFLog[idx + (1 << (exp - 1))][exp - 1]);
                }
            }
        }
    }

    int query(int const left, int const right) {
        int exp = noLargeMaxExp(right - left + 1);
#ifdef RMQ_DEBUG
        std::cout << "RMQ_DEBUG: " << exp << "\n";
#endif
        return returnMin ? std::min(dpFLog[left][exp], dpFLog[right - (1 << exp) + 1][exp]) :
            std::max(dpFLog[left][exp], dpFLog[right - (1 << exp) + 1][exp]);

    }

private:
    int noLargeMaxExp(int n) {
        int ans = 0;
        while (n > 1) {
            ans++;
            n >>= 1;
        }
        return ans;
    }

private:
    std::vector<std::vector<int>> dpFLog;
    int const INIT_FLAG = -1;
    bool returnMin;

};

#ifdef TEST_MAIN
int main() {
    std::vector<int> nums{{3, 5, 2, 5, 4, 3, 11, 9, 3, 991}};
    Rmq minObj(nums);
    std::cout << minObj.query(3, 9) << std::endl;
    std::cout << minObj.query(0, 9) << std::endl;

    Rmq maxObj(nums, false);
    std::cout << maxObj.query(3, 9) << std::endl;
    std::cout << maxObj.query(0, 6) << std::endl;
    return 0;
}
#endif
