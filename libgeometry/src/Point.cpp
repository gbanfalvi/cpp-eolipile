//
//  Point.cpp
//  lib-geometry
//
//  Created by Gabriel Banfalvi on 09/02/16.
//
//

#include "Point.hpp"


std::ostream &operator<< (std::ostream &os, Point const &point) {
    os << "Point <X:" << point.x << " Y:" << point.y << ">";
    return os;
}

