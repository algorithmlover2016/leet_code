#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

class Solution {
public:
    int numEquivDominoPairs(std::vector<std::vector<int> > const & dominoes) {
        //copy solution from https://leetcode.com/problems/number-of-equivalent-domino-pairs/discuss/340022/JavaC%2B%2BPython-Easy-and-Concise
        std::unordered_map<int, int> count;
        int res = 0;
        for (auto & dominoe : dominoes) {
            res += count[std::min(dominoe[0], dominoe[1]) * 10 + std::max(dominoe[0], dominoe[1])]++;
        }
        return res;
    }

    int numEquivDominoPairsStr(std::vector<std::vector<int> > const & dominoes) {
        //copy solution from https://leetcode.com/problems/number-of-equivalent-domino-pairs/discuss/340022/JavaC%2B%2BPython-Easy-and-Concise
        std::unordered_map<std::string, int> count;
        int res = 0;
        for (auto & dominoe : dominoes) {
            res += count[std::to_string(std::min(dominoe[0], dominoe[1])) + "@" + std::to_string(std::max(dominoe[0], dominoe[1]))]++;
        }
        return res;
    }
};

int main() {
    Solution var;
    std::vector<std::vector<int> > dominoes = {
        {1, 2}, {2, 1}, {3, 4}, {5, 6}, {4, 3}
    };
    std::cout << var.numEquivDominoPairs(dominoes) << std::endl;
    std::cout << var.numEquivDominoPairsStr(dominoes) << std::endl;
    return 0;

}
// g++ -std=c++11  -o main solution.cpp
//  g++-9 -std=c++11 solution.cpp -o main
