#include "../../head.h"


#define TEST_MAIN
class Solution {
public:
    int minimumSemester(int N, std::vector<std::vector<int>> const & relations) {
        // plagiarizing from https://github.com/luliyucoordinate/Leetcode/blob/master/src/1136-Parallel-Courses/1136.cpp
        // the difference between parallel_courses_1136 and parallel_courses_ii_1494 is
        // at one time we can only take infinite or at most k courses.
        // Because at most k, we must need know who we take and which are left. So we need record the status
        std::vector<std::vector<int>> dependents(N);
        std::vector<int> degrees(N, 0);
        for (auto const & relation : relations) {
            if (RELATION_SIZE > relation.size()) {
                continue;
            }
            int dependingCourse = relation[DEPENDENTING_IDX] - 1;
            int dependentedCourse = relation[DEPENDENTED_IDX] - 1;
            dependents[dependingCourse].emplace_back(dependentedCourse);
            degrees[dependentedCourse]++;
        }
        std::queue<int> coursesQue;
        for (int idx = 0; idx < degrees.size(); idx++) {
            if (0 == degrees[idx]) {
                coursesQue.emplace(idx);
            }
        }
        int num = 0;
        int ans = 0;
        while (!coursesQue.empty()) {
            int freeDepend = coursesQue.size();
            while (0 < freeDepend--) {
                int freeCourse = coursesQue.front(); coursesQue.pop();
                num++;
                for (auto const dependCourse : dependents[freeCourse]) {
                    if (0 == --degrees[dependCourse]) {
                        coursesQue.emplace(dependCourse);
                    }
                }
            }
            ans++;
        }
        return num == N ? ans : -1;
    }

private:
    static int const RELATION_SIZE = 2;
    static int const DEPENDENTING_IDX = 0;
    static int const DEPENDENTED_IDX = 1;
};

#ifdef TEST_MAIN
#define PRINT_TO_SCREEN
int main() {
    Solution obj;
    int N = 3;
    std::vector<std::vector<int>> relations{{{1, 3}, {2, 3}}};
    int ans = obj.minimumSemester(N, relations);
#ifdef PRINT_TO_SCREEN
    std::cout << ans << "\n";
#endif
    assert(2 == ans);

    std::vector<std::vector<int>> relations1{{{1, 2}, {2, 3}, {3, 1}}};
    ans = obj.minimumSemester(N, relations1);
#ifdef PRINT_TO_SCREEN
    std::cout << ans << "\n";
#endif
    assert(-1 == ans);
    std::cout << "TEST SUCCESSFULLY" << std::endl;
    return 0;
}
#endif
