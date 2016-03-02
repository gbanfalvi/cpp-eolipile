//
// Created by Gabriel Banfalvi on 01/02/16.
//

#ifndef EOLIPILE_QUADTREETEST_H
#define EOLIPILE_QUADTREETEST_H

#include <iostream>
#include <string>

#include "Geometry.h"

bool almostEquals(double a, double b) {
    return fabs(a-b) < 0.001;
}

void println(std::string msg) {
    std::cout << msg << std::endl;
}

void checkInstersect(std::string title, bool shouldIntersect, const Rect& rect1, const Rect& rect2) {

    SpaceIntersectAndDistance isect = rect1.intersects(rect2);

    std::cout << title << (isect.intersects ? " intersects " : " doesn't intersect ");

    if (isect.intersects) {
        std::cout << " with size " << isect.overlapSize.width << " " << isect.overlapSize.height;
    } else {
        std::cout << " with distance " << isect.distance;
    }

    std::cout << (shouldIntersect == isect.intersects ? " correct!" : " wrong!") << std::endl;
}


#endif //EOLIPILE_QUADTREETEST_H
