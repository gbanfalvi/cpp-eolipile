//
//  Point.hpp
//  lib-geometry
//
//  Created by Gabriel Banfalvi on 09/02/16.
//
//

#ifndef Point_hpp
#define Point_hpp

#include <iostream>

/// A point with an X and Y-coordinate
struct Point {
    double x = 0;
    double y = 0;

    /// Basic constructor with X and Y value
    /// \param x
    /// \param y
    Point(double x, double y):x(x), y(y){};

    /// Zero-constructor with default X Y as 0
    Point():x(0), y(0){};

    /// Copy-constructor
    /// \param point
    Point(const Point& point):x(point.x), y(point.y){};
};

std::ostream &operator<< (std::ostream &os, Point const &point);

struct PointCompare {
    inline bool operator() (const Point& lhs, const Point& rhs) const {
        return lhs.x == rhs.x ? lhs.y < rhs.y : lhs.x < rhs.x;
    }
};

#endif /* Point_hpp */
