#include "../../head.h"


// #define DEBUG
class Solution {
private:
    struct TupleComp {
        bool operator()(std::tuple<int, int> const & left,
                std::tuple<int, int> const & right) {
            if (std::get<X_AXIS>(left) < std::get<X_AXIS>(right)) {
                return true;
            }
            if (std::get<X_AXIS>(left) == std::get<X_AXIS>(right)) {
                return  std::get<Y_AXIS>(left) <= std::get<Y_AXIS>(right);
            }
            return false;
        }
    };

private:
    static int const SQUARE = 2;
    static int const POINT_LEN = 2;
    static int const POINT_NUMBER = 4;
    static int const X_AXIS = 0;
    static int const Y_AXIS = 1;
    static TupleComp tupleComp;

public:
    bool validSquare(std::vector<int> const & p1,
            std::vector<int> const & p2,
            std::vector<int> const & p3,
            std::vector<int> const & p4) {
        std::array<std::tuple<int, int>, POINT_NUMBER> points;
        if (!insertPoint(points, 0, p1) ||
                !insertPoint(points, 1, p2) ||
                !insertPoint(points, 2, p3) ||
                !insertPoint(points, 3, p4)) {
            return false;
        }
        std::sort(points.begin(), points.end(), tupleComp);
        // std::sort(points.begin(), points.end());
        #ifdef DEBUG
            std::cout << "\nElePrint\n";
            for (std::tuple<int, int> const & tEle : points) {
                std::cout << std::get<X_AXIS>(tEle) << "\t" << std::get<Y_AXIS>(tEle) << "\t";
            }
            std::cout << "\n";
        #endif
        std::tuple<int, int> diffZeroThree = minusTuple(points[3], points[0]);
        std::tuple<int, int> diffOneTwo = minusTuple(points[2], points[1]);

        return 0 != getDis(diffZeroThree) &&
            getDis(diffZeroThree) == getDis(diffOneTwo) &&
            isOrthogonal(diffZeroThree, diffOneTwo) &&
            isOrthogonal(minusTuple(points[1], points[0]), minusTuple(points[2], points[0]));


    }

    int getDis(std::tuple<int, int> const & dis) {
        return static_cast<int>(pow(std::get<X_AXIS>(dis), 2) +
            pow(std::get<Y_AXIS>(dis), 2));
    }

    bool isOrthogonal(std::tuple<int, int> const & one,
            std::tuple<int, int> const & two) {
        return 0 == (std::get<Y_AXIS>(one) * std::get<Y_AXIS>(two) +
                std::get<X_AXIS>(one) * std::get<X_AXIS>(two));
    }
    std::tuple<int, int> minusTuple(std::tuple<int, int> const & oneBegin,
            std::tuple<int, int> const & oneEnd) {
        return std::make_tuple<int, int>((std::get<X_AXIS>(oneBegin) - std::get<X_AXIS>(oneEnd)),
                (std::get<Y_AXIS>(oneBegin) - std::get<Y_AXIS>(oneEnd)));
    }

    bool insertPoint(std::array<std::tuple<int, int>, POINT_NUMBER> & points, int idx,
            std::vector<int> const & p) {
        if (idx >= points.size()) {
            return false;
        }
        int pSize = p.size();
        if (pSize < POINT_LEN) {
            return false;
        }
        points[idx] = std::make_tuple(p[X_AXIS], p[Y_AXIS]);
        #ifdef DEBUG
            std::cout << p[X_AXIS] << "\t" << p[Y_AXIS] << "\t";
            std::cout << std::get<X_AXIS>(points[idx]) << "\t" << std::get<Y_AXIS>(points[idx]) << "\n";
        #endif
        return true;
    }

};
