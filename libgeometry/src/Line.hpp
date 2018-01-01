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
#include <iostream>

struct Point;

/// Line on a plane (with no specific start or end)
struct Line {
private:
    enum LineCase { Regular, Horizontal, Vertical};

    LineCase _lineCase = Regular;
    double   _gradient = 0;
    double   _intercept = 0;

public:

    /// Line created from a gradient and a Y intercept
    /// \param gradient
    /// \param intercept
    Line(double gradient, double intercept);

    /// Line created from two points
    /// \param p1 first point
    /// \param p2 second point
    Line(Point p1, Point p2);

    /// Copy constructor
    /// \param line line to copy
    Line(const Line& line):_lineCase(line._lineCase), _gradient(line._gradient), _intercept(line._intercept){};


    /// Grradient of line
    /// \return
    double gradient() const;

    /// Intercept of line
    /// \return
    double intercept() const;

    ///  Returns whether the line is vertical. Note: Intercept is then on X axis
    /// \return true if the line is fully vertical.
    bool isVertical() const;

    /// Inverse gradient of existing line
    /// \return inverse gradient
    double inverseGradient() const;

    ///
    /// \param point
    /// \return
    Line normalWithPoint(const Point& point) const;

    /// Location of a point projected perpendicularly onto a line
    /// \param other
    /// \return
    Point pointProjectedOntoLine(const Point& other) const;

    /// X-position on line, unless the line is fully vertical, then it's Y-position
    /// \param point
    /// \return
    double valueOnLine(const Point& point) const;

};

std::ostream &operator<< (std::ostream &os, Line const &line);

#endif /* Line_hpp */
