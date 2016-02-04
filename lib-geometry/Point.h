//
// Created by Gabriel Banfalvi on 04/02/16.
//

#ifndef EOLIPILE_POINT_H
#define EOLIPILE_POINT_H

struct Point {
    double x = 0;
    double y = 0;

    Point(double x, double y):x(x), y(y){};
    Point():x(0), y(0){};
    Point(const Point& point):x(point.x), y(point.y){};
};

struct PointCompare {
    inline bool operator() (const Point& lhs, const Point& rhs) const {
        return lhs.x == rhs.x ? lhs.y < rhs.y : lhs.x < rhs.x;
    }
};

#endif //EOLIPILE_POINT_H
