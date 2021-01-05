#include "../../head.h"


class Solution {
public:
    bool canReach(std::vector<int> const & arr, int start) {
        if (arr.empty() || start >= arr.size()) {
            return false;
        }
        int const arrSize = arr.size();
        std::vector<bool> used(arrSize, false);
        return dfs(arr, used, start);
    }
    bool dfs(std::vector<int> const & arr,
            std::vector<bool> & used,
            int idx) {
        if (used[idx]) {
            return false;
        }
        if (TARGET == arr[idx]) {
            return true;
        }
        used[idx] = true;
        bool ans = false;
        int right = idx + arr[idx];
        if (right < arr.size() && dfs(arr, used, right)) {
            return true;
        }
        int left = idx - arr[idx];
        if (left > LEFT_BOUNDARY && dfs(arr, used, left)) {
            return true;
        }
        return false;
    }
private:
    static int const TARGET = 0;
    static int const LEFT_BOUNDARY = -1;
};

class Solution {
public:
    bool canReach(std::vector<int> const & arr, int start) {
        int const arrSize = arr.size();
        if (LENGTH_ZERO == arrSize || start >= arrSize) {
            return false;
        }
        std::vector<bool> used(arrSize, false);
        std::queue<int> indexes;
        indexes.emplace(start);
        while (!indexes.empty()) {
            int idx = indexes.front(); indexes.pop();
            if (TARGET == arr[idx]) {
                return true;
            }
            used[idx] = true;
            int right = idx + arr[idx];
            if (right < arrSize && !used[right]) {
                indexes.emplace(right);
            }
            int left = idx - arr[idx];
            if (left > LEFT_BOUNDARY && !used[left]) {
                indexes.emplace(left);
            }
        }
        return false;

    }
private:
    static int const TARGET = 0;
    static int const LEFT_BOUNDARY = -1;
    static int const LENGTH_ZERO = 0;
};
