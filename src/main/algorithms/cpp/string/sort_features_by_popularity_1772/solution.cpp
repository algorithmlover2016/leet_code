#include "../../head.h"

#define SPLIT_BY_GETLINE
// #define TEST_SolutionSortDepends
#define DEBUG
#define TEST_MAIN
class Solution {
public:
    std::vector<std::string> sortFeatures(std::vector<std::string> const & features,
            std::vector<std::string> const & responses) {
        std::unordered_map<std::string, std::pair<int, int>> featuresCnt; // feature as key, and pair.first is freq, second is index
        for (int idx = 0; idx < features.size(); idx++) {
            featuresCnt[features[idx]] = std::make_pair(0, idx);
        }
#ifdef DEBUG
        std::cout << "features done" << "\n";
#endif

        // statistic all the frequence of features;
        for (auto const & str : responses) {

#ifdef SPLIT_BY_GETLINE
            std::vector<std::string> ans = splitByGetLine(str, ' ');
#else 
            std::vector<std::string> ans = splitByFind(str, ' ');
#endif
            std::set<std::string> moveRepeatAns(ans.begin(), ans.end());
            for (std::string const & ele : moveRepeatAns) {
                if (featuresCnt.find(ele) != featuresCnt.end()) {
                    featuresCnt[ele].first++;
                }
            }
        }

#ifdef DEBUG
        std::cout << "split and statictic done" << "\n";
#endif
        // to construct a maxHeap need a cmp function
        auto cmp = [&] (std::tuple<std::string, int, int> const & left, std::tuple<std::string, int, int> const & right) {
            int leftCnt = std::get<STR_CNT_IDX>(left);
            int rightCnt = std::get<STR_CNT_IDX>(right);

            return leftCnt < rightCnt || (leftCnt == rightCnt && std::get<STR_IDX_IDX>(left) >= std::get<STR_IDX_IDX>(right));
        };
        typedef std::priority_queue<std::tuple<std::string, int, int>, std::vector<std::tuple<std::string, int, int>>, decltype(cmp)> MaxHeap;
        MaxHeap maxHeap(cmp);
        for (auto const & [strKey, pairVal] : featuresCnt) {
            std::tuple<std::string, int, int> tupEle = std::make_tuple(strKey, pairVal.first, pairVal.second);
            maxHeap.emplace(tupEle);
        }

        std::vector<std::string> ans;
        while (!maxHeap.empty()) {
            auto const & ele = maxHeap.top();
            ans.emplace_back(std::get<STR_ELE_IDX>(ele));
            maxHeap.pop();
        }
        return ans;

    }
private:
    std::vector<std::string> splitByGetLine(std::string const & str, char const delimeter) {
        std::vector<std::string> ans;
        std::stringstream ss(str);
        std::string item;
        while (std::getline(ss, item, delimeter)) {
            ans.emplace_back(item);
        }
        return ans;
    }

    std::vector<std::string> splitByFind(std::string const & str, char const delimeter) {
        std::vector<std::string> ans;
        std::string::size_type prePos = 0, pos = 0;
        while ((pos = str.find(delimeter, pos)) != std::string::npos) {
            ans.emplace_back(str.substr(prePos, pos - prePos));
            prePos = ++pos;
        }
        ans.emplace_back(str.substr(prePos, pos - prePos));
        return ans;
    }
private:
    static int const STR_ELE_IDX = 0;
    static int const STR_CNT_IDX = 1;
    static int const STR_IDX_IDX = 2;
};

class SolutionSortDepends {
public:
    std::vector<std::string> sortFeatures(std::vector<std::string> const & features,
            std::vector<std::string> const & responses) {
        std::unordered_map<std::string, std::pair<int, int>> featuresCnt; // feature as key, and pair.first is freq, second is index
        for (int idx = 0; idx < features.size(); idx++) {
            featuresCnt[features[idx]] = std::make_pair(0, idx);
        }
#ifdef DEBUG
        std::cout << "features done" << "\n";
#endif

        // statistic all the frequence of features;
        for (auto const & str : responses) {

#ifdef SPLIT_BY_GETLINE
            std::vector<std::string> ans = splitByGetLine(str, ' ');
#else 
            std::vector<std::string> ans = splitByFind(str, ' ');
#endif
            std::set<std::string> moveRepeatAns(ans.begin(), ans.end());
            for (std::string const & ele : moveRepeatAns) {
                if (featuresCnt.find(ele) != featuresCnt.end()) {
                    featuresCnt[ele].first++;
                }
            }
        }

#ifdef DEBUG
        std::cout << "split and statictic done" << "\n";
#endif
        // to construct a maxHeap need a cmp function
        auto cmp = [&] (std::string const & left, std::string const & right) {
            int leftCnt = featuresCnt[left].first;
            int rightCnt = featuresCnt[right].first;

            return leftCnt < rightCnt || (leftCnt == rightCnt && featuresCnt[left].second >= featuresCnt[right].second);
        };
        typedef std::priority_queue<std::string, std::vector<std::string>, decltype(cmp)> MaxHeap;
        MaxHeap maxHeap(cmp);
        for (auto const & [strKey, pairVal] : featuresCnt) {
            maxHeap.emplace(strKey);
        }

        std::vector<std::string> ans;
        while (!maxHeap.empty()) {
            auto const & ele = maxHeap.top();
            ans.emplace_back(ele);
            maxHeap.pop();
        }
        return ans;

    }
private:
    std::vector<std::string> splitByGetLine(std::string const & str, char const delimeter) {
        std::vector<std::string> ans;
        std::stringstream ss(str);
        std::string item;
        while (std::getline(ss, item, delimeter)) {
            ans.emplace_back(item);
        }
        return ans;
    }

    std::vector<std::string> splitByFind(std::string const & str, char const delimeter) {
        std::vector<std::string> ans;
        std::string::size_type prePos = 0, pos = 0;
        while ((pos = str.find(delimeter, pos)) != std::string::npos) {
            ans.emplace_back(str.substr(prePos, pos - prePos));
            prePos = ++pos;
        }
        ans.emplace_back(str.substr(prePos, pos - prePos));
        return ans;
    }
};

#ifdef TEST_MAIN
#define PRINT_TO_SCREEN

int main() {
#ifdef TEST_SolutionSortDepends
    SolutionSortDepends obj;
#else
    Solution obj;
#endif
    std::vector<std::string> features{{"cooler","lock","touch"}};
    std::vector<std::string> responses{{"i like cooler cooler", "lock touch cool", "locker like touch"}};
    std::vector<std::string> ans = obj.sortFeatures(features, responses);
#ifdef PRINT_TO_SCREEN
    for (auto const & ele : ans) {
        std::cout << ele << ", ";
    }
    std::cout << "\n";
#endif
    std::vector<std::string> expectAns{{"touch","cooler","lock"}};
    assert(ans == expectAns);

    std::vector<std::string> features1{{"a","aa","b","c"}};
    std::vector<std::string> responses1{{"a","a aa","a a a a a","b a"}};
    std::vector<std::string> ans1 = obj.sortFeatures(features1, responses1);
#ifdef PRINT_TO_SCREEN
    for (auto const & ele : ans1) {
        std::cout << ele << ", ";
    }
    std::cout << "\n";
#endif
    std::vector<std::string> expectAns1{{"a","aa","b","c"}};
    assert(ans1 == expectAns1);

    std::cout << "TEST SUCCESSFULLY" << std::endl;
    return 0;
}
#endif

