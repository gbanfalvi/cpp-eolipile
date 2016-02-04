//
// Created by Gabriel Banfalvi on 02/02/16.
//

#ifndef EOLIPILE_SPACESTRUCTS_H
#define EOLIPILE_SPACESTRUCTS_H

#include <cmath>
#include <iostream>

/* Approximate eequals */


/* Point */

struct SpacePoint {
    double x = 0;
    double y = 0;

    SpacePoint(double x, double y):x(x), y(y){};
    SpacePoint():x(0), y(0){};
    SpacePoint(const SpacePoint& point):x(point.x), y(point.y){};
};

struct SpacePointCompare {
    inline bool operator() (const SpacePoint& lhs, const SpacePoint& rhs) const {
        return lhs.x == rhs.x ? lhs.y < rhs.y : lhs.x < rhs.x;
    }
};

/* Size */

struct SpaceSize {
    double width = 0;
    double height = 0;

    SpaceSize(double width, double height):width(width), height(height){};
    SpaceSize():width(0), height(0){};
    SpaceSize(const SpaceSize& size):width(size.width), height(size.height){};
};

/* Line */

struct SpaceLine {
private:
    enum SpaceLineCase { Regular, Horizontal, Vertical};

    SpaceLineCase _lineCase = Regular;
    double _gradient = 0;
    double _intercept = 0;

public:
    SpaceLine(double gradient, double intercept);
    SpaceLine(SpacePoint p1, SpacePoint p2);
    SpaceLine(const SpaceLine& line):_lineCase(line._lineCase), _gradient(line._gradient), _intercept(line._intercept){};

    inline double inverseGradient() const;
    inline SpaceLine normalWithPoint(const SpacePoint& point) const;
    inline SpacePoint pointProjectedOntoLine(const SpacePoint& other) const;
    inline double valueOnLine(SpacePoint point);
};

/* Intersect and distance */

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
    SpaceSize overlapSize;

    SpaceIntersectAndDistance(bool intersects, double distance)
            :intersects(intersects), distance(distance), overlapSize(0,0){};

    SpaceIntersectAndDistance(bool intersects, double overlapX, double overlapY)
            :intersects(intersects), distance(0), overlapSize(overlapX,overlapY){};
};

/* Rectangle */

struct SpaceRect {
    SpacePoint origin;
    SpaceSize size;
    double rotation;

    SpaceRect(double x, double y, double width, double height, double rotation): origin(x, y), size(width, height), rotation(rotation) {};
    SpaceRect(SpacePoint origin, SpaceSize size, double rotation): origin(origin), size(size), rotation(rotation) {};
    SpaceRect(double x, double y, double width, double height): origin(x, y), size(width, height), rotation(0) {};
    SpaceRect(SpacePoint origin, SpaceSize size): origin(origin), size(size), rotation(0) {};

    /**
     * Determines if a SpaceRect overlaps another SpaceRect and either how much distance remains or overlap depth
     * returns a SpaceIntersectAndDistance
     */
    SpaceIntersectAndDistance intersects(const SpaceRect& other) const;

    inline SpacePoint center() const {

        return SpacePoint(this->origin.x + this->size.width/2,
                          this->origin.y - this->size.height/2);
    }

    inline double rotatedX(SpacePoint unrotatedSource) const {
        return this->center().x +
               cos(this->rotation) * (unrotatedSource.x - this->center().x) -
               sin(this->rotation) * (unrotatedSource.y - this->center().y);
    }

    inline double rotatedY(SpacePoint unrotatedSource) const {
        return this->center().y +
               sin(this->rotation) * (unrotatedSource.x - this->center().x) +
               cos(this->rotation) * (unrotatedSource.y - this->center().y);

    }

    inline SpacePoint rotatedPoint(SpacePoint unrotatedSource) const {
        return SpacePoint(this->rotatedX(unrotatedSource), this->rotatedY(unrotatedSource));
    }

    inline double diagonalLength() const {
        return  sqrt(pow(this->size.width, 2) + pow(this->size.height, 2));
    }

    inline SpacePoint topLeft() const {
        return this->rotatedPoint(this->origin);
    }

    inline SpacePoint topRight() const {
        return this->rotatedPoint(SpacePoint(this->origin.x + this->size.width,
                                             this->origin.y));
    }

    inline SpacePoint bottomLeft() const {
        return this->rotatedPoint(SpacePoint(this->origin.x,
                                             this->origin.y - this->size.height));
    }

    inline SpacePoint bottomRight() const {
        return this->rotatedPoint(SpacePoint(this->origin.x + this->size.width,
                                             this->origin.y - this->size.height));
    }

};


#endif //EOLIPILE_SPACESTRUCTS_H
