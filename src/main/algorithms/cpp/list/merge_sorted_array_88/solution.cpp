#include "../../head.h"



class SolutionSpaceMPlusN {
public:
    void merge(std::vector<int> & nums1, int m, std::vector<int> & nums2, int n) {
        std::vector<int> res(m + n);
        int lindex = 0, rindex = 0, index = 0;
        while(lindex < m && rindex < n) {
            // std::cout << "lindex: " << lindex << "\trindex: " << rindex << "\n";
            if(nums1[lindex] < nums2[rindex]) {
                res[index] = nums1[lindex++];
            } else {
                res[index] = nums2[rindex++];
            }
            index++;
        }
        for (; lindex < m; lindex++) {
            res[index++] = nums1[lindex];
        }
        for (; rindex < n; rindex++) {
            res[index++] = nums2[rindex];
        }
       nums1.swap(res);
    }
};

class SolutionReverseFromEndToStart {
public:
    void merge(std::vector<int> & nums1, int m, std::vector<int> const & nums2, int n) {
        int i = m-1;
        int j = n-1;
        int k = m+n-1;

        while (i >= 0 && j >= 0) {
            if (nums1[i] >= nums2[j]) {
                nums1[k] = nums1[i];
                i--;
            } else {
                nums1[k] = nums2[j];
                j--;
            }
            k--;
        }

        while (i >= 0) {
            nums1[k] = nums1[i];
            k--;
            i--;
        }

        while(j >= 0) {
            nums1[k] = nums2[j];
            k--;
            j--;
        }
    }
};
