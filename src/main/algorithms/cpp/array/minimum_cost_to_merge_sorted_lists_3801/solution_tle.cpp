#include "../../head.h"


#define __DEBUG__
class Solution {
public:
    long long minMergeCost(vector<vector<int>> lists) {
        int len = lists.size();
        if (len < 2) {
            return 0;
        }
        int totalCost = INT_MAX;
        for (int idx = 0; idx < len; idx++) {
            for (int innerIdx = idx + 1; innerIdx < len; innerIdx++) {
                #ifdef __DEBUG__
                std::cout << "Considering merging lists at index " << idx << "whose median is " << lists[idx][(lists[idx].size() - 1)/2]
                << " and " << innerIdx << " whose median is " << lists[innerIdx][(lists[innerIdx].size() - 1)/2] << std::endl;
                #endif
                int cost = lists[idx].size() + lists[innerIdx].size() + abs(lists[idx][(lists[idx].size() - 1)/2] - lists[innerIdx][(lists[innerIdx].size() - 1)/2]);

                #ifdef __DEBUG__
                std::cout << "Merging lists at index " << idx << " and " << innerIdx << " with cost " << cost << std::endl;
                #endif

                std::vector<int> merged = mergeTwoLists(lists[idx], lists[innerIdx]);

                #ifdef __DEBUG__
                std::cout << "Merged list: ";
                for (int num : merged) {
                    std::cout << num << " ";
                }
                std::cout << std::endl;
                #endif

                std::vector<std::vector<int>> newLists(lists);
                auto idxIter = newLists.begin() + idx;
                auto innerIdxIter = newLists.begin() + innerIdx;
                if (innerIdx > idx) {
                    innerIdxIter--;
                }
                newLists.erase(idxIter);
                newLists.erase(innerIdxIter);
                newLists.push_back(merged);
                #ifdef __DEBUG__
                std::cout << "New lists after merging: " << std::endl;
                for (const auto & lst : newLists) {
                    for (int num : lst) {
                        std::cout << num << " ";
                    }
                    std::cout << std::endl;
                }
                #endif
                cost += minMergeCost(newLists);
                totalCost = std::min(totalCost, cost);
                #ifdef __DEBUG__
                std::cout << "Total cost after merging lists at index " << idx << " and " << innerIdx << " is " << totalCost << std::endl;
                #endif
            }
        }
        return totalCost;

        
    }
private:
    std::vector<int> mergeTwoLists(
        const std::vector<int> & list1,
        const std::vector<int> & list2) {
        std::vector<int> merged;
        merged.reserve(list1.size() + list2.size());
        int idx1 = 0, idx2 = 0;
        while (idx1 < list1.size() && idx2 < list2.size()) {
            if (list1[idx1] < list2[idx2]) {
                merged.push_back(list1[idx1++]);
            } else {
                merged.push_back(list2[idx2++]);
            }
        }
        while (idx1 < list1.size()) {
            merged.push_back(list1[idx1++]);
        }
        while (idx2 < list2.size()) {
            merged.push_back(list2[idx2++]);
        }
        return merged;
    }
};