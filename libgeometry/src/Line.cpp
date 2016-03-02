//
//  Line.cpp
//  lib-geometry
//
//  Created by Gabriel Banfalvi on 09/02/16.
//
//

#include "Line.hpp"

Line::Line(double gradient, double intercept):_gradient(gradient), _intercept(intercept) {
    if (_gradient == 0) {
        _lineCase = Horizontal;
        
    } else if (_gradient == INFINITY) {
        _lineCase = Vertical;
    }
}

Line::Line(Point p1, Point p2) {
    if (p1.x == p2.x && p1.y == p2.y) {
        throw;
        
    } else if (p1.x == p2.x) {
        _gradient = INFINITY;
        _intercept = p1.x;
        _lineCase = Vertical;
        
    } else if (p1.y == p2.y) {
        _gradient = 0;
        _intercept = p1.y;
        _lineCase = Horizontal;
        
    } else {
        _gradient = (p2.y - p1.y) / (p2.x - p1.x);
        _intercept = p2.y - _gradient*p2.x;
    }
}