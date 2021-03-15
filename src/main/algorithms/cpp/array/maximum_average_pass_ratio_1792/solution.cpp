#include "../../head.h"


// #define DEBUG
class Solution {
public:
    double maxAverageRatio(std::vector<std::vector<int>> const & classes, int extraStudents) {
        // plagiarizing from https://youtu.be/ZjydWQCVg80
        auto cmp = [](std::tuple<double, int, int> const & left, std::tuple<double, int, int> const & right) {
            // we need a minHeap
            return std::get<RATIO_DIFF_IDX>(left) > std::get<RATIO_DIFF_IDX>(right);
        };
        typedef std::priority_queue<std::tuple<double, int, int>, std::vector<std::tuple<double, int, int>>, decltype(cmp)> MaxHeap;
        MaxHeap minHeap(cmp);
        for (auto const & ele : classes) {
            if (CLASS_SIZE > ele.size()) {
                continue;
            }
            double passNum = ele[PASS_NUM_IDX];
            double tatolNum = ele[TOTAL_NUM_IDX];
            // a / b <= (a + 1) / (b + 1) when 0 < a <= b
            // which means a * (b + 1) = a * b + a <= (a + 1) * b = a * b + b. because  0 < a <= b
            // so the diff is negative, the max diff, will be most small in minHeap;
            minHeap.emplace(std::make_tuple(passNum / tatolNum - (passNum + 1) / (tatolNum + 1),
                        ele[PASS_NUM_IDX], ele[TOTAL_NUM_IDX]));
        }
        while (extraStudents-- > 0) {
            auto const & ele = minHeap.top();
            int newPassNum = std::get<PASS_IDX>(ele) + 1;
            int newTotalNum = std::get<TOTAL_IDX>(ele) + 1;
            #ifdef DEBUG
            std::cout << "cur ratio: " << std::get<RATIO_DIFF_IDX>(ele) << ": "  << newPassNum << ", " << newTotalNum << "\n";
            #endif
            minHeap.pop();
            minHeap.emplace(std::make_tuple(
                        (double) (newPassNum) / (double)(newTotalNum) - (double) (newPassNum + 1) / (double) (newTotalNum + 1),
                        newPassNum,
                        newTotalNum));
        }
        double ans = 0;
        int totalClassNum = classes.size();
        while (!minHeap.empty()) {
            auto const & ele = minHeap.top();
            ans += (double)std::get<PASS_IDX>(ele) / (double)(std::get<TOTAL_IDX>(ele));
            minHeap.pop();
        }
        return ans / totalClassNum;
    }
private:
    static int const RATIO_DIFF_IDX = 0;
    static int const PASS_IDX = 1;
    static int const TOTAL_IDX = 2;
    static int const CLASS_SIZE = 2;
    static int const PASS_NUM_IDX = 0;
    static int const TOTAL_NUM_IDX = 1;
};
