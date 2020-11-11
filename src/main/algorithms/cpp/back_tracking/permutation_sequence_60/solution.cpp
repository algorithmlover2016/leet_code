#include "../../head.h"


class Solution {
public:
    std::string getPermutation(int n, int k) {
        // plagiarizing fro https://leetcode.com/problems/permutation-sequence/discuss/22507/%22Explain-like-I'm-five%22-Java-Solution-in-O(n)
        std::list<char> nums;
        // compute the factorial numbers from 1 to n(include);
        std::vector<int> facNums(n + 1, 1);
        for (int index = 1; index < facNums.size(); index++) {
            facNums[index] = index * facNums[index - 1];
            // to form the sequence number
            nums.emplace_back(index + '0');
        }
        // int facRes = factorial(n);

        k--; // index from zero not one

        std::string ans;
        std::list<char>::iterator it;
        for (int index = 1; index <= n; index++) {
            int curIndex = k / facNums[n - index];
            it = nums.begin();
            std::advance(it, curIndex);
            ans += *it;
            nums.erase(it);
            k -= curIndex * facNums[n - index];
        }
        return ans;
    }

    int factorial(int n) {
        if (n < 2) {
            return 1;
        }
        return n * factorial(n - 1);
    }
};

class Solution {
public:
    std::string getPermutation(int n, int k) {
        // plagarizing from https://leetcode.com/problems/permutation-sequence/discuss/22544/Easy-understand-Most-concise-C%2B%2B-solution-minimal-memory-required
        int facNum = factorial(n);
        std::string nstr(n, '1');
        for (int index = 0; index < n; index++) {
            nstr[index] += index;
        }
        // std::cout << nstr << "\n";
        k--;
        for (int index = 0; index < n; index++) {
            facNum /= n - index;
            int curIdx = index + k / facNum;
            // std::cout << "facNum: " << facNum << "\tindex: " << index << "\tcurIdx: " << curIdx << "\tk: " << k << "\n";
            k -= (curIdx - index) * facNum;
            char c = nstr[curIdx];
            for (; curIdx > index; curIdx--) {
                nstr[curIdx] = nstr[curIdx - 1];
            }
            nstr[index] = c;
        }
        return nstr;
    }


    int factorial(int n) {
        if (n < 2) {
            return 1;
        }
        return n * factorial(n - 1);
    }
};
