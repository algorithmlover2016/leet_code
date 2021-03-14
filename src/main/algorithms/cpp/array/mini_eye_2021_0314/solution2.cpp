#include <iostream>
#include <vector>

void print(std::vector<std::vector<char>> const & nums) {
}

int main() {
    int N = 0;
    
    std::cin >> N;
    std::vector<int> nums(N);
    for (int idx = 0; idx < nums.size(); idx++) {
        std::cin >> nums[idx];
    }
    for (int idx = 0; idx < nums.size(); idx++) {
        int n = nums[idx];
        std::vector<std::vector<char>> ans(n, std::vector<char>(n, ' '));
        int status = 0; // status (0, right), (1, down), (2, left), (3, up)
        int row = 0;
        int col = 0;
        bool over = false;
        while (!over) {
            ans[row][col] = '#';
            switch (status) {
                case 0:
                    while (true) {
                        col++;
                        if (col == n || (col + 1 < n && ans[row][col + 1] == '#')) {
                            col--;
                            row++;
                            status = 1;
                            if (row == n || (row + 1 < n && ans[row + 1][col] == '#')) {
                                over = true;
                            }
                            break;
                        } else {
                            ans[row][col] = '#';
                        }
                    }
                    break;
                case 1:
                    while (true) {
                        row++;
                        if (row == n || (row + 1 < n && ans[row + 1][col] == '#')) {
                            row--;
                            col--;
                            status = 2;
                            if (col < 0 || (col - 1 >= 0 && ans[row][col - 1] == '#')) {
                                over = true;
                            }
                            break;
                        } else {
                            ans[row][col] = '#';
                        }
                    }
                    break;
                case 2:
                    while (true) {
                        col--;
                        if (col < 0 || (col - 1 >= 0 && ans[row][col - 1] == '#')) {
                            col++;
                            row--;
                            status = 3;
                            if (row <= 1 || (ans[row - 1][col] == '#')) {
                                over = true;
                            }
                            break;
                        } else {
                            ans[row][col] = '#';
                        }
                    }
                    break;
                case 3:
                    while (true) {
                        row--;
                        if (row <= 1 || (row - 1 >= 0 && ans[row - 1][col] == '#')) {
                            row++;
                            col++;
                            status = 0;
                            if (col == n || (col + 1 < n && ans[row][col + 1] == '#')) {
                                over = true;
                            }
                            break;
                        } else {
                            ans[row][col] = '#';
                        }
                    }
                    break;

                default:
                    break;
            }
        }
        for (int row = 0; row < ans.size(); row++) {
            for (int col = 0; col < ans.size(); col++) {
                std::cout << ans[row][col];
            }
            std::cout << "\n";
        }

    }
    return 0;
}
