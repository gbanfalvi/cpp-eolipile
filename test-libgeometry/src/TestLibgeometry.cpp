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

    // -- Points
    beginTestSection("Points");

    Point p0;
    testTrue(p0.x == 0 && p0.y == 0, "Zero constructor should create point set to 0,0.");

    Point p1(2, 3);
    testTrue(p1.x == 2 && p1.y == 3, "Reg. constructor should create point set to 2,3.");

    Point p2(p1);
    testTrue(p2.x == 2 && p2.y == 3, "Copy constructor should create point set to 2,3.");

    p2.x = -4.5;
    p2.y = -7;
    testTrue(p2.x == -4.5, "Changed x prop. should be -4.5.");
    testTrue(p2.y == -7, "Changed y prop. should be -7.");

    endTestSection();

    // -- Sizes
    beginTestSection("Sizes");

    Size s0;
    testTrue(s0.width == 0 && s0.height == 0, "Zero constructor size should be set to 0x0.");

    Size s1(9, 8);
    testTrue(s1.width == 9 && s1.height == 8, "Reg. constructor size should be set to 9x8.");

    Size s2(s1);
    testTrue(s2.width == 9 && s2.height == 8, "Copy constructor size should be set to 9x8.");

    s2.width = 12;
    s2.height = 45;
    testTrue(s2.width == 12, "Changed width prop. should be 12.");
    testTrue(s2.height == 45, "Changed height prop. should be 45.");

    endTestSection();

    // -- Lines
    beginTestSection("Lines");

    // Horizontal line
    logComment("🌀 Horizontal line y = 0x + 1");

    Line l0 = Line(0, 1);
    testTrue(l0.gradient() == 0, "Gradient should be 0.");
    testTrue(l0.intercept() == 1, "Y-intercept should be 1.");
    testTrue(l0.inverseGradient() == INFINITY, "Line's inverse gradient should be vertical (INFINITY).");
    testTrue(l0.isVertical() == false, "Should be recognized as NOT vertical.");

    Point normalPoint0 = Point(1,1);

    logComment("Horizontal line with normal from 1,1.");

    Line l0normal0 = l0.normalWithPoint(normalPoint0);  // Should be vertical
    testTrue(l0normal0.gradient() == INFINITY, "Normal line's gradient should be vertical (INFINITY).");
    testTrue(l0normal0.intercept() == 1, "Normal line's intercept on X-axis should be 1."); // Note: Normal intercepts on X-axis
    testTrue(l0normal0.isVertical() == true, "Normal line should be recognized as vertical.");

    logComment("Horizontal line with point at 2,2 projected onto it.");

    Point l0proj0 = l0.pointProjectedOntoLine(Point(2,2));
    testTrue(l0proj0.x == 2 && l0proj0.y == 1, "Point should be projected onto line at 2,1.");

    logComment("Horizontal line with point at -2,-2 projected onto it.");

    Point l0proj1 = l0.pointProjectedOntoLine(Point(-2,-2));

    testTrue(l0proj1.x == -2 && l0proj1.y == 1, "Point should be projected onto line at -2,1.");


    // Diagonal line
    logComment("🌀 Diagonal line y = x + 2");

    Line l1 = Line(1, 2);
    testTrue(l1.gradient() == 1, "Gradient should be 1.");
    testTrue(l1.intercept() == 2, "Intercept should be 2.");
    testTrue(l1.inverseGradient() == -1, "Inverse gradient -1.");
    testTrue(l1.isVertical() == false, "Line is NOT vertical.");

    logComment("Diagonal line with normal from 0,4.");

    Line l1normal0 = l1.normalWithPoint(Point(0, 4));
    testTrue(l1normal0.gradient() == -1, "Normal's gradient should be 1.");
    testTrue(l1normal0.intercept() == 4, "Normal's intercept should be 4.");

    logComment("Diagonal line with normal from -2,-4.");

    Line l1normal1 = l1.normalWithPoint(Point(-2, -4));
    testTrue(l1normal1.gradient() == -1, "Normal's gradient should also be -1.");
    testTrue(l1normal1.intercept() == -6, "Normal's intercept should be -6.");

    logComment("Diagonal line with normal from 0,0.");

    Line l1normal2 = l1.normalWithPoint(Point(0, 0));
    testTrue(l1normal2.gradient() == -1, "Normal's gradient should also be -1");
    testTrue(l1normal2.intercept() == 0, "Normal's intercept should be 0");

    logComment("Diagonal line with normal from -1,3.");

    Line l1normal3 = l1.normalWithPoint(Point(-1, 3));
    testTrue(l1normal3.gradient() == -1, "Normal's gradient should also be 0");
    testTrue(l1normal3.intercept() == 2, "Normal's intercept should be 2");

    logComment("Diagonal line with point at -1,-1 projected onto it.");

    Point l1proj0 = l1.pointProjectedOntoLine(Point(-1,-1));
    testTrue(l1proj0.x == -2 && l1proj0.y == 0, "Point should be projected onto line at -2,0");

    logComment("Diagonal line with point at 1,2 projected onto it.");

    Point l1proj1 = l1.pointProjectedOntoLine(Point(1,2));
    testTrue(l1proj1.x == 0.5 && l1proj1.y == 2.5, "Point should be projected onto line at 0.5,2.5");

    logComment("🌀 Diagonal line y = -2x - 1");

    Line l2 = Line(-2, -1);
    testTrue(l2.gradient() == -2, "Gradient should be -2");
    testTrue(l2.intercept() == -1, "Intercept should be -1");
    testTrue(l2.inverseGradient() == 0.5, "Inverse gradient should be 0.5");

    logComment("🌀 Equivalent lines");

    logComment("Lines w/ points -1,-1 to 1,1 and 2,2 to -2,-2.");
    Line l3a = Line(Point(-1,-1), Point(1,1));
    Line l3b = Line(Point(2,2), Point(-2,-2));

    testTrue(l3a.gradient() == l3b.gradient(), "Gradients should be equivalent.");
    testTrue(l3a.intercept() == l3b.intercept(), "Intercepts should be equivalent.");

    logComment("Lines w/ points -4,0 to 2,0 and 10,0 to 4,0.");
    Line l4a = Line(Point(-4,0), Point(2,0));
    Line l4b = Line(Point(10,0), Point(4,0));

    testTrue(l4a.gradient() == l4b.gradient(), "Gradients should be equivalent.");
    testTrue(l4a.intercept() == l4b.intercept(), "Intercepts should be equivalent.");
    testTrue(l4a.isVertical() == l4b.isVertical() && l4a.isVertical() == false, "Neither should be vertical.");

    logComment("Lines w/ points 2,1 to 2,4 and 2,3 to 2,5.");
    Line l5a = Line(Point(2,1), Point(2,4));
    Line l5b = Line(Point(2,3), Point(2,5));

    testTrue(l5a.gradient() == l5b.gradient(), "Gradients should be equivalent.");
    testTrue(l5a.intercept() == l5b.intercept(), "Intercepts should be equivalent.");
    testTrue(l5a.isVertical() == l5b.isVertical() && l5a.isVertical() == true, "Both should be vertical.");

    logComment("🌀 Vertical line y = ∞x + 4");

    Line l6 = Line(INFINITY, 4);
    testTrue(l6.gradient() == INFINITY, "Line's gradient is INFINITY.");
    testTrue(l6.intercept() == 4, "Line's X-intercept is 4.");
    testTrue(l6.inverseGradient() == 0, "Line's inverse gradient is 0");



    //printCout("Test line:");
    //printCout("Line: ", l0, " Point: ", normalPoint0, " Normal: ", l0normal0);

    endTestSection();

    return 0;

}
