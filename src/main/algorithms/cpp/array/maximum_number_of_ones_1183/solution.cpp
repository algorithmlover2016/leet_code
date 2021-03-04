#include "../../head.h"


#define TEST_MAIN
class Solution {
public:
    int maximumNumberOfOnes(int width, int height, int sideLength, int maxOnes) {
        if (1 >= sideLength) {
            if (0 == maxOnes) {
                return 0;
            } else {
                return width * height;
            }

        }
        std::vector<int> cnt(sideLength * sideLength, 0);
        for (int w = 0; w < width; w++) {
            for (int h = 0; h < height; h++) {
                int mapW = w % sideLength;
                int mapH = h % sideLength;
                cnt[mapW * sideLength + mapH]++;
            }
        }
        std::sort(cnt.begin(), cnt.end(), [](int i, int j) {
                return i > j;
                });
        int ans = 0;
        for (int ones = 0; ones < maxOnes; ones++) {
            // each time we need to find the maxNum at cnt if we have a posibility to set 1;
            ans += cnt[ones];
        }

        return ans;
    }
};
#ifdef TEST_MAIN
#define PRINT_TO_SCREEN
int main() {
    Solution obj;
    int ans1 = obj.maximumNumberOfOnes(3, 3, 2, 1);
#ifdef PRINT_TO_SCREEN
    std::cout << "3, 3, 2, 1: " << ans1 << "\n";
#endif

    int ans2 = obj.maximumNumberOfOnes(3, 3, 2, 2);
#ifdef PRINT_TO_SCREEN
    std::cout << "3, 3, 2, 2: " << ans2 << "\n";
#endif
    assert(ans1 == 4);
    assert(ans2 == 6);
    std::cout << "TEST SUCCESSFULLY" << std::endl;
}
#endif
