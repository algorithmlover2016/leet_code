#include "../../head.h"
class MajorityChecker {
public:
    MajorityChecker(std::vector<int> const & arr) {
#ifdef SORTED
        std::unordered_map<int, std::vector<int> > tmpEleIdxs;
#endif

        for (int index = 0; index < arr.size(); index++) {
#ifndef SORTED
            eleIdxs[arr[index]].emplace_back(index);
#else 
            tmpEleIdxs[arr[index]].emplace_back(index);
#endif
        }

#ifdef SORTED
        for (auto & tmpEleIdx : tmpEleIdxs) {
            eleIdxs.emplace_back({tmpEleIdx.first, tmpEleIdx.second});
        }
        std::sort(std::begin(eleIdxs), std::end(eleIdxs), 
                [ ](auto & eleIdx1, auto & eleIdx2) {return eleIdx1.second.size() > eleIdx2.second.size()})
#endif
    }
    
    int query(const int left, const int right, const int threshold) {
        for (auto & eleIdx : eleIdxs) {
            if (eleIdx.second.size() < threshold) {
#ifndef SORTED
                continue;
#else
                break;
#endif
            }
            // std::vector<int>::iterator it_left, it_right;
            auto it_left = std::lower_bound(std::begin(eleIdx.second), std::end(eleIdx.second), left);
            auto it_right = std::upper_bound(std::begin(eleIdx.second), std::end(eleIdx.second), right);
            if (it_right - it_left >= threshold) {
                return eleIdx.first;
            }

        }
        return -1;
    }

#ifndef SORTED
    std::unordered_map<int, std::vector<int> > eleIdxs;
#else
    std::vector<std::pair<int, std::vector<int> > eleIdxs;
#endif

};

int main() {
    std::vector<int> dominoes = {
        1, 1, 2, 2, 1, 1,
    };
    MajorityChecker var(dominoes);
    std::cout << var.query(0, 5, 4) << std::endl;
    std::cout << var.query(0, 3, 3) << std::endl;
    std::cout << var.query(2, 3, 2) << std::endl;
    return 0;

}
// g++ -std=c++11  -o main solution.cpp
//  g++-9 -std=c++11 solution.cpp -o main
