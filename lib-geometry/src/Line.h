//
// Created by Gabriel Banfalvi on 04/02/16.
//

#ifndef EOLIPILE_LINE_H
#define EOLIPILE_LINE_H

#include <cmath>
#include "Point.h"

struct Line {
private:
    enum LineCase { Regular, Horizontal, Vertical};

    LineCase _lineCase = Regular;
    double _gradient = 0;
    double _intercept = 0;

public:
    Line(double gradient, double intercept);
    Line(Point p1, Point p2);
    Line(const Line& line):_lineCase(line._lineCase), _gradient(line._gradient), _intercept(line._intercept){};

    inline double inverseGradient() const {
        if (this->_lineCase == Horizontal) {
            return INFINITY;

        } else if (this->_lineCase == Vertical) {
            return 0;

        } else {
            return -1 / this->_gradient;
        }
    }

    inline Line normalWithPoint(const Point& point) const {
        if (this->_lineCase == Horizontal) {
            return Line(INFINITY, point.x);

        } else if (this->_lineCase == Vertical) {
            return Line(0, point.y);

        } else {
            return Line(this->inverseGradient(), point.y - this->inverseGradient()*point.x);
        }
    }

    inline Point pointProjectedOntoLine(const Point& other) const {
        if (this->_lineCase == Vertical) {
            return Point(this->_intercept, other.y);

        } else if (this->_lineCase == Horizontal){
            return Point(other.x, this->_intercept);

        } else {
            double otherGradient = this->inverseGradient();
            double otherIntercept = other.y - otherGradient*other.x;

            double intersectX = (this->_intercept - otherIntercept)/(otherGradient - this->_gradient);
            double intersectY = this->_gradient*intersectX + this->_intercept;

            return Point(intersectX, intersectY);
        }
    }

    inline double valueOnLine(const Point& point) const {
        Point projected = this->pointProjectedOntoLine(point);
        if (this->_lineCase == Vertical) {
            return projected.y;
        } else {
            return projected.x;
        }
    }
};

#endif //EOLIPILE_LINE_H
