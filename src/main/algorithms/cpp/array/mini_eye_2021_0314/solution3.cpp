#include <iostream>
#include <vector>


// #define DEBUG
#define MATH_COMPUTE_LAYER
int main() {
    std::vector<int> directions{{0, 1, 0, -1, 0}};
    int N = 0;
    int M = 0;
    
    std::cin >> N >> M;
    std::vector<std::vector<int>> nums(N, std::vector<int>(M));
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < M; col++) {
            std::cin >> nums[row][col];
        }
    }
    int ans = 0;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < M; col++) {
            if (0 == nums[row][col]) {
                continue;
            }
#ifdef MATH_COMPUTE_LAYER
            int cover = 0;
            for (int directIdx = 0; directIdx < 4; directIdx++) {
                int nR = row + directions[directIdx];
                int nC = col + directions[directIdx + 1];
                if (nR >= 0 && nR < N && nC >= 0 && nC < M) {
                    cover += std::min(nums[nR][nC], nums[row][col]);
                }
            }
#ifdef DEBUG
            std::cout << row << ", " << col << ": " << cover << "; ";
#endif
            ans += nums[row][col] * 6 - (nums[row][col] - 1) * 2 - cover;
#else
            for (int idx = 1; idx <= nums[row][col]; idx++) {
                int cover = 0;
                for (int d = 0; d < 4; d++) {
                    int nR = row + directions[d];
                    int nC = col + directions[d + 1];
                    if (nR >= 0 && nR < N && nC >= 0 && nC < M && nums[nR][nC] >= idx) {
                        cover++;
                    }
                }
                if (idx < nums[row][col]) {
                    cover++;
                }
                if (idx > 1) {
                    cover++;
                }
                ans += 6 - cover;
            }
#endif
        }
    }

#ifdef DEBUG
    std::cout << "\n";
#endif

    std::cout << ans << std::endl;

    return 0;
}
