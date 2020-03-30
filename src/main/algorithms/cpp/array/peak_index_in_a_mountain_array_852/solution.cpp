#include <vector>
#include <iostream>

class Solution_BSI {
public:
    int peakIndexInMountainArray(std::vector<int>& A) {
        int size = A.size();
        if (size < 3) {
            return -1;
        }
        int low = 0;
        int high = size - 1;
        while (low < high) {
            int mid = (low + high) >> 1;
            int midNext = mid + 1;
            /*
            int midPre = mid - 1;
            if ((A[mid] > A[midNext]) && (A[mid] > A[midPre])) {
                return mid;
            }
            */

            if (A[mid] > A[midNext]) {
                high = mid;
            } else {
                low = midNext;
            }
        }
        return low;
    }
};

class Solution_Iter {
public:
    int peakIndexInMountainArray(vector<int>& a) {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        for(int i=1; i+1<a.size(); ++i) {
            if(a[i-1] <= a[i] && a[i] >= a[i+1]) {
                return i;
            }
        }
        return 0;
    }
};

int main() {
    return 0;
}
