#include "../../head.h"


class Solution {
public:
    std::vector<int> searchRange(std::vector<int> const & nums, int target) {
        if (nums.empty()) {
            return {-1,  -1};
        }
        // trick idea
        std::vector<int>::const_iterator low = std::lower_bound(nums.begin(), nums.end(), target);
        if (low == nums.end() || target != *low)  {
            return {-1, -1};
        }
        std::vector<int>::const_iterator up = std::upper_bound(nums.begin(), nums.end(), target);
        return {static_cast<int>(low - nums.begin()), static_cast<int>(std::prev(up) - nums.begin())};

    }
};

class Solution {
public:
    std::vector<int> searchRange(std::vector<int> const & nums, int target) {
        if (nums.empty()) {
            return {-1,  -1};
        }
        // trick idea
        std::vector<int>::const_iterator low = my_lower_bound(nums.begin(), nums.end(), target);
        if (low == nums.end() || target != *low)  {
            return {-1, -1};
        }
        std::vector<int>::const_iterator up = my_upper_bound(nums.begin(), nums.end(), target);
        return {static_cast<int>(low - nums.begin()), static_cast<int>(std::prev(up) - nums.begin())};
    }
private:
    template <class ForwardIterator, class T>
        ForwardIterator my_lower_bound (ForwardIterator first, ForwardIterator last, const T& val) {
            ForwardIterator it;
            typename std::iterator_traits<ForwardIterator>::difference_type count, step;
            count = std::distance(first, last); // last is not counted
            while (count > 0) {
                it = first;
                step = count / 2;
                std::advance (it,step);
                if (*it < val) {                 // or: if (comp(*it,val)), for version (2)
                    first = ++it;
                    count -= step + 1;
                } else {
                    count=step;
                }
            }
            return first;
        }
    template <class ForwardIterator, class T>
        ForwardIterator my_upper_bound (ForwardIterator first, ForwardIterator last, const T& val) {
            ForwardIterator it;
            typename std::iterator_traits<ForwardIterator>::difference_type count, step;
            count = std::distance(first,last);
            while (count > 0) {
                it = first;
                step=count/2;
                std::advance (it,step);
                if (!(val < *it)) {                 // or: if (!comp(val,*it)), for version (2)
                    first = ++it;
                    count -= step + 1;
                } else {
                    count=step;
                }
            }
            return first;
        }
};

class Solution {
public:
    int first(std::vector<int> const & arr,int low, int high, int x) {
        int ans = -1;
        while (high - low > 1) {
            int mid = low + (high - low) / 2;
            if(arr[mid] == x) {
                ans = mid;
                high = mid-1;
            } else if(arr[mid] < x) {
                low = mid + 1;
            } else {
                high = mid-1;
            }
        }

        if (arr[low] == x) {
            return low;
        }
        if (arr[high] == x) {
            return high;
        }
        return ans;
    }

    int last(std::vector<int> const & arr, int low, int high, int x) {
        int ans=-1;
        while(high - low > 1) {
            int mid=low + (high - low) / 2;
            if(arr[mid] == x) {
                ans = mid;
                low = mid + 1;
            } else if(arr[mid] > x) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }


        }

        if (arr[high] == x) {
            return high;
        }
        if (arr[low] == x) {
            return low;
        }
        return ans;

    }

    std::vector<int> searchRange(std::vector<int> const & nums, int target) {
        std::vector<int>ans(2, -1);
        if (nums.size() == 0) {
            return ans;
        }
        int l = first(nums, 0, nums.size() - 1, target);
        int r = last(nums, 0, nums.size() - 1, target);
        ans[0] = l,ans[1] = r;
        return ans;
    }
};
