#include "../../head.h"


class Solution {
public:
    int totalFruit(std::vector<int> const & tree) {
        int target = 2;
        int res = 0, start = 0;
        std::unordered_map<int, int> visited;
        for (int index = 0; index < tree.size(); index++) {
            if (0 == visited[tree[index]]++) {
                target--;
            }
            while (0 > target && start <= index) {
                if (0 == --visited[tree[start++]]) {
                    target++;
                }
            }
            if (0 <= target) {
                res = std::max(res, index - start + 1);
            }
        }
        return res;
    }
};

class Solution {
public:
    int totalFruit(vector<int>& tree) {

        int first_fruit = -1;
        int second_fruit= -1;
        int count_first_fruit = 0;
        int current_max = 0;
        int maxm = 0 ;

        for (auto curr_fruit : tree) {
            if (curr_fruit == first_fruit || curr_fruit == second_fruit) {
                current_max++;
            } else {
                current_max = count_first_fruit + 1;
            }

            if (curr_fruit == first_fruit) {
                count_first_fruit++;
            } else {
                count_first_fruit = 1;
            }

            if (curr_fruit != first_fruit) {
                second_fruit = first_fruit;
                first_fruit = curr_fruit;
            }

            maxm = std::max(current_max, maxm);
        }
        return maxm;
    }
};

static auto x = []() {ios_base::sync_with_stdio(false); cin.tie(NULL); return NULL; }();

class Solution {
public:
    int totalFruit(std::vector<int> const & tree) {
        int n = tree.size();
        // b record the second fruit and how many it's collected
        int size = 0, same_count = 0, a = 0, b = 0, cur = 0;
        int res = 0;  // final answer

        for (int i = 0; i < n; i++) {
            int cur=tree[i];
            if (cur == b) {
                size++;
                same_count++;
            } else if(cur == a) {
                size++;
                same_count = 1;
                a = b;
                b = cur;
            } else {
                size = same_count + 1;
                same_count = 1;
                a = b;
                b = cur;
            }
            res = std::max(res, size);
        }
        return res;
    }
};

class Solution {
public:
    int totalFruit(std::vector<int> const & tree) {
        std::unordered_map<int, int> count;
        int i, j;
        for (i = 0, j = 0; j < tree.size(); ++j) {
            count[tree[j]]++;
            /*
               count.size() > 2, means we add a new different element into it. because the end index add one,
               so the start index should be added one, too. Only in this way ,we maintain the longest window;
               only when count.size() <= 2, the windows maybe get longer;
               */
            if (count.size() > 2) {
                if (--count[tree[i]] == 0) {
                    count.erase(tree[i]);
                }
                i++;
            }
        }
        return j - i;
    }
};

class Solution {
public:
    int totalFruit(std::vector<int> const & tree) {
        // plagiarizing from https://leetcode-cn.com/problems/number-of-subarrays-with-bounded-maximum/solution/xi-fa-dai-ni-xue-suan-fa-yi-ci-gao-ding-qian-zhu-2/
        return atMost(2, tree);
    }

    int atMost(int k, std::vector<int> const & tree) {
        int ans = 0;
        std::unordered_map<int, int> count;
        for (int left = 0, right = 0; right < tree.size(); right++) {
            if (JUST_ZERO == count[tree[right]]++) {
                // have not visited this type
                k -= 1;
            }
            while (JUST_ZERO > k) {
                if (JUST_ZERO == --count[tree[left++]]) {
                    k += 1;
                }
            }
            ans = std::max(ans, right - left + 1);
        }
        return ans;
    }

private:
    static int const JUST_ZERO = 0;
};
