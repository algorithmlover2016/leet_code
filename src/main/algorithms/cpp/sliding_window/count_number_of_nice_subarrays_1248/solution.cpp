#include "../../head.h"


class Solution {
public:
    int numberOfSubarrays(std::vector<int> const & nums, int K) {
        // plagiarizing from https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/discuss/516977/JavaC++Python-Easy-and-Concise
        return atMost(nums, K) - atMost(nums, K - 1);
    }
    int atMost(std::vector<int> const & nums, int K) {
        int res = 0;
        int start = 0;
        std::unordered_map<int, int> visited; // can be replaced by vector<int>(3, 0) c - 'a';
        for (int index = 0; index < nums.size(); index++) {
            // std::cout << "num: " << nums[index] << "\t";
            if (nums[index] & 0x01) {
                K--;
            }
            visited[nums[index]]++;
            while (K < 0) {
                --visited[nums[start]];
                if (nums[start] & 0x01) {
                    K++;
                }
                start++;
            }
            // std::cout << "ans: " << index - start + 1 << "\n";
            res += index - start + 1;
        }
        return res;
    }
};

class Solution {
public:
    int numberOfSubarrays(std::vector<int> const & nums, int K) {
        // plagiarizing from https://leetcode.com/problems/count-number-of-nice-subarrays/discuss/419378/JavaC%2B%2BPython-Sliding-Window-atMost(K)-atMost(K-1)
        int res = 0, cnt = 0, start = 0;
        for (int index = 0; index < nums.size(); index++) {
            if (nums[index] & 0x01) {
                K--;
                cnt = 0; // a new combination
            }
            while (0 == K) {
                K += (nums[start++] & 0x01);
                cnt++; //create a new combination or can remove even number
            }
            res += cnt;
        }
        return res;
    }
};
