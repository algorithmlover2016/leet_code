#include "../../head.h"



class Solution {
public:
    int minMovesToMakePalindrome(std::string const & s) {
        // plagiarizing from https://leetcode.com/problems/minimum-number-of-moves-to-make-palindrome/discuss/1822174/C%2B%2BPython-Short-Greedy-Solution
        // and https://leetcode.com/problems/minimum-number-of-moves-to-make-palindrome/discuss/1821936/List-vs.-BIT

        /*
        For a palindrome, if we make a swap in the left (right) part, then we can make the same swap in the right (left) part.
        After the swap, the palindrome will be changed, however, we do not care about it.
        So, the swaps in left (right) part, can be equal to same swaps in right (left) part. Namely, we just need consider either side.
        We keep left (right) side unchanged, and make swaps on the other side. If we do minimum swaps, the number will be the answer.
        */

        std::list<char> lStr(std::begin(s), std::end(s));
        int ans = 0;
        while (lStr.size() > 1 /* If there is no character or just one, it is already a Palindrome */) {
            int step = 0;
            std::list<char>::iterator it = std::begin(lStr);
            for (; (*it) != lStr.back(); it++) {
                step++; // find the first letter which is equal to lStr.back(); we keep right side unchanged.
            }
            if (lStr.size() - 1 == step) {
                // the last letter which is lStr.back() is uniqe, and should be placed in the center. and lStr.size() is odd number
                ans += step / 2;
            } else {
                ans += step;
                lStr.erase(it);
            }
            lStr.erase(std::prev(std::end(lStr)));
        }
        return ans;
    }
};

// #define DEBUG
class SolutionBIT {
public:
    int minMovesToMakePalindrome(std::string const & s) {
        // plagiarizing from https://leetcode.com/problems/minimum-number-of-moves-to-make-palindrome/discuss/1821936/List-vs.-BIT
        // BIT solution
        if (s.empty()) {
            return 0;
        }

        int sSize = s.size();
        bits.resize(sSize + 1, 0);
        std::vector<std::deque<int>> posIdxs(LOWERCASE_ENG_LEN);

        for (int idx = 0; idx < sSize; idx++) {
            int letter = s[idx] - OFFSET;
            posIdxs[letter].emplace_back(idx);
        }

        int ans = 0;
        for (int idx = sSize - 1; idx >= 0; idx--) {
            int letter = s[idx] - OFFSET; // the letter is the most right letter
            if (!posIdxs[letter].empty()) {
                int pos = posIdxs[letter].front() - prefixSum(posIdxs[letter].front(), bits); // we need know how many letter + OFFSET appears times;
                #ifdef DEBUG
                std::cout << "idx: " << s[idx] << ", mov: " << pos << ", front: " << posIdxs[letter].front() << "\n";
                #endif
                // we need move this letter to the most left front and it have to been moved to the begining position and it must past all the different letter
                // and if the same letter, there is no need to swap. The former same letter has been used. So there is no need to swap.
                add(posIdxs[letter].front(), 1, bits);
                #ifdef DEBUG
                std::cout << "prefix_sum: " << prefixSum(posIdxs[letter].front(), bits) << "\n";
                #endif
                if (posIdxs[letter].size() > 1) {
                    // it is not the center letter.
                    posIdxs[letter].pop_front();
                } else {
                    pos /= 2;
                }
                ans += pos;
                posIdxs[letter].pop_back();
            }
        }
        return ans;
    }
private:
    void add(int idx, int val, std::vector<int> & bits) {
        #ifdef DEBUG_BIT
        std::cout << "input idx: " << idx << "\n";
        #endif
        for (int bitIdx = idx + 1; bitIdx < bits.size(); bitIdx += (bitIdx & (-bitIdx))) {
            bits[bitIdx] += val;
            #ifdef DEBUG_BIT
            std::cout << "add bitIdx: " << bitIdx << ", " << bits[bitIdx] << "; ";
            #endif
        }
        #ifdef DEBUG_BIT
        std::cout << '\n';
        #endif
    }

    int prefixSum(int idx, std::vector<int> & bits) {
        int sum = 0;
        for (int bitIdx = idx + 1; bitIdx > 0; bitIdx -= (bitIdx & (-bitIdx))) {
            sum += bits[bitIdx];
        }
        return sum;
    }
private:
    // constexpr static int const MAX_LEN = 2000;
    std::vector<int> bits;
    constexpr char static OFFSET = 'a';
    constexpr int static LOWERCASE_ENG_LEN = 26;
};