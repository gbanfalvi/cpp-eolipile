//
//  main.cpp
//  lib-geometry-test
//
//  Created by Gabriel Banfalvi on 09/02/16.
//  Copyright © 2016 clueless. All rights reserved.
//

#include "TestLibgeometry.hpp"

#include <iostream>
#include <assert.h>
#include "Geometry.hpp"

int main(__unused int argc, __unused const char * argv[]) {

    printCout(" -- Starting tests");

    // -- Points

    printCout(" -- Testing Points");

    Point p0;
    assert(p0.x == 0);
    assert(p0.y == 0);

    Point p1(2, 3);
    assert(p1.x == 2);
    assert(p1.y == 3);


    Point p2(p1);
    assert(p2.x == 2);
    assert(p2.y == 3);

    p2.x = -4.5;
    p2.y = -7;
    assert(p2.x == -4.5);
    assert(p2.y == -7);

    // -- Sizes

    printCout(" -- Testing Sizes");

    Size s0;
    assert(s0.width == 0);
    assert(s0.height == 0);

    Size s1(9, 8);
    assert(s1.width == 9);
    assert(s1.height == 8);

    Size s2(s1);
    assert(s2.width == 9);
    assert(s2.height == 8);

    s2.width = 12;
    s2.height = 45;
    assert(s2.width == 12);
    assert(s2.height == 45);

    // -- Lines

    printCout(" -- Testing Lines");

    Line l0 = Line(0, 1);
    assert(l0.gradient() == 0);
    assert(l0.intercept() == 1);
    assert(l0.inverseGradient() == INFINITY);
    assert(l0.isVertical() == false);

    Point normalPoint0 = Point(1,1);

    Line l0normal0 = l0.normalWithPoint(normalPoint0);
    assert(l0normal0.gradient() == INFINITY);
    assert(l0normal0.intercept() == 1); // Note: Normal intercepts on X-axis
    assert(l0normal0.isVertical() == true);

    Point l0proj0 = l0.pointProjectedOntoLine(Point(2,2));
    assert(l0proj0.x == 2);
    assert(l0proj0.y == 1);

    Point l0proj1 = l0.pointProjectedOntoLine(Point(-2,-2));
    assert(l0proj1.x == -2);
    assert(l0proj1.y == 1);

    //printCout("Test line:");
    //printCout("Line: ", l0, " Point: ", normalPoint0, " Normal: ", l0normal0);


    Line l1 = Line(1, 2);
    assert(l1.gradient() == 1);
    assert(l1.intercept() == 2);
    assert(l1.inverseGradient() == -1);


    Line l2 = Line(2, 3);
    assert(l2.gradient() == 2);
    assert(l2.intercept() == 3);
    assert(l2.inverseGradient() == -0.5);

    Line l3 = Line(INFINITY, 4);
    assert(l3.gradient() == INFINITY);
    assert(l3.intercept() == 4);
    assert(l3.inverseGradient() == 0);


    return 0;

}
