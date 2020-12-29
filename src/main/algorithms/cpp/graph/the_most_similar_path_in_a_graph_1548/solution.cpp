#include "../../head.h"

// #define DEBUG
// #define TEST_2
class Solution {
public:
    std::vector<int> mostSimilar(int n,
            std::vector<std::vector<int>> const & roads,
            std::vector<std::string> const & names,
            std::vector<std::string> const targetPath) {

        // construct the graph
        std::vector<std::vector<int>> graph(n);
        for (auto const & road : roads) {
            if (ROAD_LEN != road.size()) {
                continue;
            }
            graph[road[ROAD_S]].emplace_back(road[ROAD_E]);
            graph[road[ROAD_E]].emplace_back(road[ROAD_S]);
        }

        int const targetPathSize = targetPath.size();
        std::vector<std::vector<int>> dpMemo(targetPathSize + 1,
                std::vector<int>(n, 0));
        std::vector<std::vector<int>> parents(targetPathSize + 1,
                std::vector<int>(n, -1));

        for (int stepIdx = 1; stepIdx < dpMemo.size(); stepIdx++) {
            for (int city = 0; city < n; city++) {
                dpMemo[stepIdx][city] = INT_MAX;
                for (auto const uCity : graph[city]) {
                    if (dpMemo[stepIdx][city] > dpMemo[stepIdx - 1][uCity]) {
                        dpMemo[stepIdx][city] = dpMemo[stepIdx - 1][uCity];
                        parents[stepIdx][city] = uCity;
                    }
                }
                dpMemo[stepIdx][city] += (names[city] == targetPath[stepIdx - 1]) ? 0 : 1;
            }
#ifdef DEBUG
                std::cout << "stepIdx element: " << stepIdx << "\n";
                for (auto const ele : dpMemo[stepIdx]) {
                    std::cout << ele << "\t";
                }
                std::cout << "\n";
#endif
        }

#ifdef DEBUG
        std::cout << "last step element\n";
        for (auto const ele : dpMemo[targetPathSize]) {
            std::cout << ele << "\t";
        }
        std::cout << "\n";
#endif
        int targetEndCity = std::min_element(dpMemo[targetPathSize].begin(),
                dpMemo[targetPathSize].end()) - dpMemo[targetPathSize].begin();
#ifdef DEBUG
        std::cout << "targetEndCity: " << targetEndCity << "\n";
#endif

        std::vector<int> ans(targetPathSize, targetEndCity);
        for (int step = targetPathSize; step > 1; step--) {
            targetEndCity = parents[step][targetEndCity];
            ans[step - 2] = targetEndCity;
#ifdef DEBUG
            std::cout << "reverse City: " << targetEndCity << "\n";
#endif
        }
        return ans;
    }
private:
    static int const ROAD_LEN = 2;
    static int const ROAD_S = 0;
    static int const ROAD_E = 1;
};

int main() {

#ifdef TEST_2
    int n = 4;
    std::vector<std::vector<int>> roads{{{1, 0}, {2, 0}, {3, 0}, {2, 1}, {3, 1}, {3, 2}}};
    std::vector<std::string> names{{"ATL", "PEK", "LAX", "DXB"}};
    std::vector<std::string> targetPath{{"ABC", "DEF", "GHI",
        "JKL", "HNO", "PQR", "STU", "VWX"}};

#elif defined(TEST_1)
    int n = 5;
    std::vector<std::vector<int>> roads{{{0, 2}, {0, 3}, {1, 2}, {1, 3}, {1, 4}, {2, 4}}};
    std::vector<std::string> names{{"ATL", "PEK", "LAX", "DXB", "HND"}};
    std::vector<std::string> targetPath{{"ATL", "DXB", "HND", "LAX"}};

#else
// #if !defined(TEST_1) && !defined(TEST_2)
    int n = 6;
    std::vector<std::vector<int>> roads{{{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}}};
    std::vector<std::string> names{{"ATL", "PEK", "LAX", "ATL", "DXB", "HND"}};
    std::vector<std::string> targetPath{{"ATL", "DXB", "HND", "DXB", "ATL", "LAX", "PEK"}};
    std::vector<int> expectAns{{3, 4, 5, 4, 3, 2, 1}};
#endif

    Solution obj;
    std::vector<int> ans = obj.mostSimilar(n, roads, names, targetPath);

#if defined(DEBUG) || defined(TEST_2) || defined(TEST_1)
    for (auto const num : ans) {
        std::cout << num << "\t";
    }
    std::cout << std::endl;
#endif

#if !defined(TEST_1) && !defined(TEST_2)
    assert(ans == expectAns);
#endif
    return 0;
}
