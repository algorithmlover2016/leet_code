#include "../../head.h"


class Solution {
public:
    bool isRectangleCover(std::vector<std::vector<int>> const & rectangles) {
        // plagiarizing from https://leetcode.com/problems/perfect-rectangle/discuss/87181/Really-Easy-Understanding-Solution(O(n)-Java)
        if (rectangles.empty()) {
            return false;
        }
        int buttomLeftX = INIT_MAX;
        int buttomLeftY = INIT_MAX;
        int topRightX = INIT_MIN;
        int topRightY = INIT_MIN;
        int area = 0;
        std::unordered_set<std::string> recordCorners;
        std::pair<std::unordered_set<std::string>::iterator, bool> it;
        for (auto const & rectangle : rectangles) {
            if (RECTANGLE_POINT_SIZE > rectangle.size()) {
                continue;
            }
            int const cornerLeftX = rectangle[BUTTON_LEFT_X_IDX];
            int const cornerLeftY = rectangle[BUTTON_LEFT_Y_IDX];
            int const cornerRightX = rectangle[BUTTON_RIGHT_X_IDX];
            int const cornerRightY = rectangle[BUTTON_RIGHT_Y_IDX];

            // record the X axis of the most left corner
            buttomLeftX = std::min(buttomLeftX, cornerLeftX);
            // record the Y axis of the most left corner
            buttomLeftY = std::min(buttomLeftY, cornerLeftY);
            // record the X axis of the most right corner
            topRightX = std::max(topRightX, cornerRightX);
            // record the Y axis of the most right corner
            topRightY = std::max(topRightY, cornerRightY);

            area += (cornerRightX - cornerLeftX) * (cornerRightY - cornerLeftY);

            std::string buttomLeftCorner = std::to_string(cornerLeftX) + SPLIT_LETTER + std::to_string(cornerLeftY);
            std::string topLeftCorner = std::to_string(cornerLeftX) + SPLIT_LETTER + std::to_string(cornerRightY);

            std::string buttomRightCorner = std::to_string(cornerRightX) + SPLIT_LETTER + std::to_string(cornerLeftY);
            std::string topRightCorner = std::to_string(cornerRightX) + SPLIT_LETTER + std::to_string(cornerRightY);
            it = recordCorners.insert(buttomLeftCorner);
            if (!it.second) {
                // we have insert the corner before, which means the corner appeared before;
                recordCorners.erase(it.first);
            }
            it = recordCorners.insert(topLeftCorner);
            if (!it.second) {
                // we have insert the corner before, which means the corner appeared before;
                recordCorners.erase(it.first);
            }
            it = recordCorners.insert(buttomRightCorner);
            if (!it.second) {
                // we have insert the corner before, which means the corner appeared before;
                recordCorners.erase(it.first);
            }
            it = recordCorners.insert(topRightCorner);
            if (!it.second) {
                // we have insert the corner before, which means the corner appeared before;
                recordCorners.erase(it.first);
            }
        }
        std::string buttomLeftCorner = std::to_string(buttomLeftX) + SPLIT_LETTER + std::to_string(buttomLeftY);
        std::string topLeftCorner = std::to_string(buttomLeftX) + SPLIT_LETTER + std::to_string(topRightY);

        std::string buttomRightCorner = std::to_string(topRightX) + SPLIT_LETTER + std::to_string(buttomLeftY);
        std::string topRightCorner = std::to_string(topRightX) + SPLIT_LETTER + std::to_string(topRightY);
        if (recordCorners.find(buttomLeftCorner) == recordCorners.end() ||
                recordCorners.find(topLeftCorner) == recordCorners.end() ||
                recordCorners.find(buttomRightCorner) == recordCorners.end() ||
                recordCorners.find(topRightCorner) == recordCorners.end() ||
                RECTANGLE_POINT_SIZE != recordCorners.size()) {
            return false;
        }
        return area == (topRightX - buttomLeftX) * (topRightY - buttomLeftY);
    }

private:
    static char const SPLIT_LETTER = '@';
    static int const RECTANGLE_POINT_SIZE = 4;
    static int const BUTTON_LEFT_X_IDX = 0;
    static int const BUTTON_LEFT_Y_IDX = 1;
    static int const BUTTON_RIGHT_X_IDX = 2;
    static int const BUTTON_RIGHT_Y_IDX = 3;

    static int const INIT_MAX = INT_MAX;
    static int const INIT_MIN = INT_MIN;
};

class Solution {
public:
    // plagiarizing from https://leetcode.com/problems/perfect-rectangle/discuss/87180/O(n)-solution-by-counting-corners-with-detailed-explaination
    struct pairhash {
        //double hash function for pair key
    public:
        template <typename T, typename U>
        size_t operator()(const pair<T, U> & rhs) const {
            size_t l = std::hash<T>()(rhs.first);
            size_t r = std::hash<U>()(rhs.second);
            return l + 0x9e3779b9 + (r << 6) + (r >> 2);
        }
    };

    bool isRectangleCover(std::vector<std::vector<int>> const & rectangles) {
        // step 1: counting
        std::unordered_map<pair<int, int>, int, pairhash> corner_count;
        int minx = INT_MAX, maxx=INT_MIN, miny=INT_MAX, maxy=INT_MIN;
        for (auto & rect : rectangles) {
            minx = std::min(minx, rect[0]);
            maxx = std::max(maxx, rect[2]);
            miny = std::min(miny, rect[1]);
            maxy = std::max(maxy, rect[3]);

            int & m1 = corner_count[std::make_pair(rect[0], rect[1])];
            if (m1 & 1) {
                return false;
            } else {
                m1 |= 1;
            }
            int & m2 = corner_count[std::make_pair(rect[2], rect[1])];
            if (m2 & 2) {
                return false;
            } else {
                m2 |= 2;
            }
            int & m3 = corner_count[std::make_pair(rect[0], rect[3])];
            if (m3 & 4) {
                return false;
            } else {
                m3 |= 4;
            }
            int & m4 = corner_count[std::make_pair(rect[2], rect[3])];
            if (m4 & 8) {
                return false;
            } else {
                m4 |= 8;
            }
        }

        //step2: checking
        for (const auto & kv: corner_count) {
            std::pair<int, int> pos;
            int mask;
            std::tie(pos, mask) = kv;
            if ((pos.first != minx && pos.first != maxx) || (pos.second != miny && pos.second != maxy)) {
                if (mask != 3 && mask != 5 && mask != 10 && mask != 12 && mask != 15) {
                    return false;
                }
            }
        }
        return true;
    }
};

// python from https://leetcode.com/problems/perfect-rectangle/discuss/87189/Short-corner-xor-solution
/*
    def isRectangleCover(self, rectangles):
        area = 0
        corners = set()
        a, c = lambda: (X - x) * (Y - y), lambda: {(x, y), (x, Y), (X, y), (X, Y)}
        for x, y, X, Y in rectangles:
            area += a()
            corners ^= c()
        x, y, X, Y = (f(z) for f, z in zip((min, min, max, max), zip(*rectangles)))
        return area == a() and corners == c()
   */
