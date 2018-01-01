
#include "Line.hpp"
#include "Point.hpp"

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

double Line::gradient() const {
    return _gradient;
}

double Line::intercept() const {
    return _intercept;
}

bool Line::isVertical() const {
    return _lineCase == Vertical;
}

double Line::inverseGradient() const {
    if (_lineCase == Horizontal) {
        return INFINITY;

    } else if (_lineCase == Vertical) {
        return 0;

    } else {
        return -1 / _gradient;
    }
}

Line Line::normalWithPoint(const Point& point) const {
    if (_lineCase == Horizontal) {
        return Line(INFINITY, point.x);

    } else if (_lineCase == Vertical) {
        return Line(0, point.y);

    } else {
        return Line(inverseGradient(), point.y - inverseGradient()*point.x);
    }
}

Point Line::pointProjectedOntoLine(const Point& other) const {
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

double Line::valueOnLine(const Point& point) const {
    Point projected = pointProjectedOntoLine(point);
    if (_lineCase == Vertical) {
        return projected.y;
    } else {
        return projected.x;
    }
}

std::ostream &operator<< (std::ostream &os, Line const &line) {
    os << "Line <Gradient:" << line.gradient() << " Intercept:" << line.intercept() << ">";
    return os;
}




