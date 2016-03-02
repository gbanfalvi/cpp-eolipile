//
// Created by Gabriel Banfalvi on 04/02/16.
//

#ifndef EOLIPILE_RECT_H
#define EOLIPILE_RECT_H

#include <cmath>

#include "Size.h"
#include "Point.h"
#include "Line.h"

/**
 * SpaceIntersectAndDistance.intersects specifies whether the rectangles intersect or not.
 *
 * SpaceIntersectAndDistance.distance specifies the estimated remaining distance between thier nearest points.
 *  it's a rough calculation,but it's guaranteed to not intersect, 0 if they do intersect.
 *
 * SpaceIntersectAndDistance.overlapSize specifies the overlap relative to the first object, relative to its orientation
 */
struct SpaceIntersectAndDistance {
    bool intersects;
    double distance;
    Size overlapSize;

    SpaceIntersectAndDistance(bool intersects, double distance)
            :intersects(intersects), distance(distance), overlapSize(0,0){};

    SpaceIntersectAndDistance(bool intersects, double overlapX, double overlapY)
            :intersects(intersects), distance(0), overlapSize(overlapX,overlapY){};
};


struct Rect {
    Point origin;
    Size size;
    double rotation;

    Rect(double x, double y, double width, double height, double rotation): origin(x, y), size(width, height), rotation(rotation) {};
    Rect(Point origin, Size size, double rotation): origin(origin), size(size), rotation(rotation) {};
    Rect(double x, double y, double width, double height): origin(x, y), size(width, height), rotation(0) {};
    Rect(Point origin, Size size): origin(origin), size(size), rotation(0) {};

    /**
     * Determines if a SpaceRect overlaps another SpaceRect and either how much distance remains or overlap depth
     * returns a SpaceIntersectAndDistance
     */
    SpaceIntersectAndDistance intersects(const Rect& other) const;

    inline Point center() const {

        return Point(this->origin.x + this->size.width/2,
                          this->origin.y - this->size.height/2);
    }

    inline double rotatedX(Point unrotatedSource) const {
        return this->center().x +
               cos(this->rotation) * (unrotatedSource.x - this->center().x) -
               sin(this->rotation) * (unrotatedSource.y - this->center().y);
    }

    inline double rotatedY(Point unrotatedSource) const {
        return this->center().y +
               sin(this->rotation) * (unrotatedSource.x - this->center().x) +
               cos(this->rotation) * (unrotatedSource.y - this->center().y);

    }

    inline Point rotatedPoint(Point unrotatedSource) const {
        return Point(this->rotatedX(unrotatedSource), this->rotatedY(unrotatedSource));
    }

    inline double diagonalLength() const {
        return  sqrt(pow(this->size.width, 2) + pow(this->size.height, 2));
    }

    inline Point topLeft() const {
        return this->rotatedPoint(this->origin);
    }

    inline Point topRight() const {
        return this->rotatedPoint(Point(this->origin.x + this->size.width,
                                             this->origin.y));
    }

    inline Point bottomLeft() const {
        return this->rotatedPoint(Point(this->origin.x,
                                             this->origin.y - this->size.height));
    }

    inline Point bottomRight() const {
        return this->rotatedPoint(Point(this->origin.x + this->size.width,
                                             this->origin.y - this->size.height));
    }

};


#endif //EOLIPILE_RECT_H
