#include "../../head.h"

class SolutionBetterRuntime {
public:
    struct pt {
        int x, y, cnt;
        pt( int px, int py ) : x(px), y(py), cnt(1) {
        }
    };

    struct line {
        int px, py, slantx, slanty, cnt;
        line( int x, int y, int sx, int sy, int pcnt )
        {
            px = x, py = y;
            slantx = sx, slanty = sy;
            cnt = pcnt;
        }
    };

    int maxPoints(std::vector<std::vector<int>> & points) {
        int i, j, n = points.size();
        for(i = 1; i < n; i++) {
            std::swap(points[i], points[rand() % (i+1)]);
        }
        bool find;
        int maxpt = 0;

        std::vector<pt> uniquept;
        std::vector<line> Lines;

        for(i = 0; i < n; ++i) {
            find = false;
            for(auto& p : uniquept) {
                if( p.x == points[i][0] && p.y == points[i][1] ) {
                    p.cnt++;
                    find = true;
                    break;
                }
            }

            if(!find) {
                uniquept.push_back(pt(points[i][0], points[i][1]));
            }
        }

        n = uniquept.size();
        if (n < 2) {
            return !n ? 0 : uniquept[0].cnt;
        }

        for (i = 1; i < n; ++i) {
            find = false;
            for (auto& l : Lines) {
                long long w = l.px - uniquept[i].x;
                long long h = l.py - uniquept[i].y;

                if(w*l.slanty == h*l.slantx) {
                    l.cnt += uniquept[i].cnt;
                    find = true;
                    // how to avoid two line make a cross?
                    // for example: [[1,5],[2,4],[5,5],[4,4],[3,3], [2, 2], [1,1],[4,2]]
                    break;
                }
            }

            if(!find) {
                for (j = 0; j < i; ++j) {
                    Lines.push_back(line(uniquept[i].x,
                                           uniquept[i].y,
                                           uniquept[j].x - uniquept[i].x,
                                           uniquept[j].y - uniquept[i].y,
                                           uniquept[i].cnt + uniquept[j].cnt));
                }
            }
        }

        for (i = 0; i < Lines.size(); ++i) {
            maxpt = std::max(maxpt, Lines[i].cnt);
        }

        return maxpt;
    }
};
// auto chimberGang = []() {std::ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);return 0;}();

class Solution {
public:
    int maxPoints(std::vector<std::vector<int>> const & points) {
        //plagiarizing from https://leetcode.com/problems/max-points-on-a-line/discuss/47113/A-java-solution-with-notes
        int const pSize = points.size();
        if (pSize < 3) {
            return pSize;
        }

        int ans = 0;
        for (int i = 0; i < pSize; i++) {
            std::unordered_map<int, std::unordered_map<int, int>> slotXYCnt;
            int overLap = 0, specialPMax = 0;
            for (int j = i + 1; j < pSize; j++) {
                int deltaX = points[j][0] - points[i][0];
                int deltaY = points[j][1] - points[i][1];
                if ((0 == deltaX) && (0 == deltaY)) {
                    overLap++;
                    continue;
                }

                int gcd = generateGCD(deltaX, deltaY);
                deltaX /= gcd;
                deltaY /= gcd;
                if (slotXYCnt.find(deltaX) == slotXYCnt.end()) {
                    std::unordered_map<int, int> tmp({{deltaY, 1}});
                    slotXYCnt.emplace(deltaX, tmp);
                } else {
                    if (slotXYCnt[deltaX].find(deltaY) == slotXYCnt[deltaX].end()) {
                        slotXYCnt[deltaX].emplace(deltaY, 1);
                    } else {
                        slotXYCnt[deltaX][deltaY]++;
                    }
                }
                // std::cout << "i, j: " << i << ", " << j << " slotXYCnt[deltaX][deltaY] : " << slotXYCnt[deltaX][deltaY] << "\n";
                specialPMax = std::max(specialPMax, slotXYCnt[deltaX][deltaY]);
            }
            ans = std::max(specialPMax + overLap + 1, ans);
        }
        return ans;
    }


    // if a == 0, return b; if b == 0, return a; otherwise return gcd of (a, b)
    // for example generateGCD(12, 0) = 12; generateGCD(0, 15) = 15; generateGCD(12, 15) = 3;
    int generateGCD(int a, int b) {
        if (0 == b) {
            return a;
        }
        return generateGCD(b, a % b);
    }

};
