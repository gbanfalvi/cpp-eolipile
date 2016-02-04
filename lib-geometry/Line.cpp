//
// Created by Gabriel Banfalvi on 04/02/16.
//



#include "Line.h"

Line::Line(double gradient, double intercept):_gradient(gradient), _intercept(intercept) {
    if (this->_gradient == 0) {
        this->_lineCase = Horizontal;

    } else if (this->_gradient == INFINITY) {
        this->_lineCase = Vertical;
    }
}

Line::Line(Point p1, Point p2) {
    if (p1.x == p2.x && p1.y == p2.y) {
        throw;

    } else if (p1.x == p2.x) {
        this->_gradient = INFINITY;
        this->_intercept = p1.x;
        this->_lineCase = Vertical;

    } else if (p1.y == p2.y) {
        this->_gradient = 0;
        this->_intercept = p1.y;
        this->_lineCase = Horizontal;

    } else {
        this->_gradient = (p2.y - p1.y) / (p2.x - p1.x);
        this->_intercept = p2.y - this->_gradient*p2.x;
    }
}
