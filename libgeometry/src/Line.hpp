//
//  Line.hpp
//  lib-geometry
//
//  Created by Gabriel Banfalvi on 09/02/16.
//
//

#ifndef Line_hpp
#define Line_hpp

#include <cmath>
struct Point;

struct Line {
private:
    enum LineCase { Regular, Horizontal, Vertical};

    LineCase _lineCase = Regular;
    double   _gradient = 0;
    double   _intercept = 0;

public:
    Line(double gradient, double intercept);
    Line(Point p1, Point p2);
    Line(const Line& line):_lineCase(line._lineCase), _gradient(line._gradient), _intercept(line._intercept){};

    double inverseGradient() const;
    Line normalWithPoint(const Point& point) const;
    Point pointProjectedOntoLine(const Point& other) const;
    double valueOnLine(const Point& point) const;
};

#endif /* Line_hpp */
