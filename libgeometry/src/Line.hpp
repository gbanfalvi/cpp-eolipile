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
#include "Point.hpp"

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
        if (_lineCase == Horizontal) {
            return INFINITY;
            
        } else if (_lineCase == Vertical) {
            return 0;
            
        } else {
            return -1 / _gradient;
        }
    }
    
    inline Line normalWithPoint(const Point& point) const {
        if (_lineCase == Horizontal) {
            return Line(INFINITY, point.x);
            
        } else if (_lineCase == Vertical) {
            return Line(0, point.y);
            
        } else {
            return Line(inverseGradient(), point.y - inverseGradient()*point.x);
        }
    }
    
    inline Point pointProjectedOntoLine(const Point& other) const {
        if (_lineCase == Vertical) {
            return Point(_intercept, other.y);
            
        } else if (_lineCase == Horizontal){
            return Point(other.x, _intercept);
            
        } else {
            double otherGradient = inverseGradient();
            double otherIntercept = other.y - otherGradient*other.x;
            
            double intersectX = (_intercept - otherIntercept)/(otherGradient - _gradient);
            double intersectY = _gradient*intersectX + _intercept;
            
            return Point(intersectX, intersectY);
        }
    }
    
    inline double valueOnLine(const Point& point) const {
        Point projected = pointProjectedOntoLine(point);
        if (_lineCase == Vertical) {
            return projected.y;
        } else {
            return projected.x;
        }
    }
};


#endif /* Line_hpp */
