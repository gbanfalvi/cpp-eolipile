//
// Created by Gabriel Banfalvi on 02/02/16.
//

#include "SpaceStructs.h"

SpaceLine::SpaceLine(double gradient, double intercept):_gradient(gradient), _intercept(intercept) {
    if (this->_gradient == 0) {
        this->_lineCase = Horizontal;

    } else if (this->_gradient == INFINITY) {
        this->_lineCase = Vertical;
    }
}

SpaceLine::SpaceLine(SpacePoint p1, SpacePoint p2) {
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

inline double SpaceLine::inverseGradient() const {
    if (this->_lineCase == Horizontal) {
        return INFINITY;

    } else if (this->_lineCase == Vertical) {
        return 0;

    } else {
        return -1 / this->_gradient;
    }
}

inline SpaceLine SpaceLine::normalWithPoint(const SpacePoint& point) const {
    if (this->_lineCase == Horizontal) {
        return SpaceLine(INFINITY, point.x);

    } else if (this->_lineCase == Vertical) {
        return SpaceLine(0, point.y);

    } else {
        return SpaceLine(this->inverseGradient(), point.y - this->inverseGradient()*point.x);
    }
}

inline SpacePoint SpaceLine::pointProjectedOntoLine(const SpacePoint& other) const {
    if (this->_lineCase == Vertical) {
        return SpacePoint(this->_intercept, other.y);

    } else if (this->_lineCase == Horizontal){
        return SpacePoint(other.x, this->_intercept);

    } else {
        double otherGradient = this->inverseGradient();
        double otherIntercept = other.y - otherGradient*other.x;

        double intersectX = (this->_intercept - otherIntercept)/(otherGradient - this->_gradient);
        double intersectY = this->_gradient*intersectX + this->_intercept;

        return SpacePoint(intersectX, intersectY);
    }
}

inline double SpaceLine::valueOnLine(SpacePoint point) {
    SpacePoint projected = this->pointProjectedOntoLine(point);
    if (this->_lineCase == Vertical) {
        return projected.y;
    } else {
        return projected.x;
    }
}

/* Rectangle */

SpaceIntersectAndDistance SpaceRect::intersects(const SpaceRect& other) const {
    double radiusSelf = this->diagonalLength() / 2;
    double radiusOther = other.diagonalLength() / 2;

    SpacePoint centerSelf = this->center();
    SpacePoint centerOther = other.center();

    double centerDistance = sqrt(pow(centerOther.x - centerSelf.x, 2) + pow(centerOther.y - centerSelf.y, 2));

    if (centerDistance <= radiusSelf + radiusOther) {

        double minSelfX = 0, maxSelfX = 0,
                minOtherX = 0, maxOtherX = 0,
                overlappingDistanceX = 0;


        SpaceLine line1 = SpaceLine(this->topRight(), this->bottomRight()).normalWithPoint(this->bottomRight());

        double valueLeft = line1.valueOnLine(this->bottomLeft());
        double valueRight = line1.valueOnLine(this->bottomRight());

        minSelfX = fmin(valueLeft, valueRight);
        maxSelfX = fmax(valueLeft, valueRight);

        minOtherX = fmin(
                fmin( line1.valueOnLine(other.bottomLeft()), line1.valueOnLine(other.bottomRight()) ),
                fmin( line1.valueOnLine(other.topLeft()),    line1.valueOnLine(other.topRight())    )
        );

        maxOtherX = fmax(
                fmax( line1.valueOnLine(other.bottomLeft()), line1.valueOnLine(other.bottomRight()) ),
                fmax( line1.valueOnLine(other.topLeft()), line1.valueOnLine(other.topRight())       )
        );

        if (minOtherX <= minSelfX && maxOtherX <= minSelfX) {
            return SpaceIntersectAndDistance(false, minSelfX - maxOtherX);

        } else if (maxOtherX >= maxSelfX && minOtherX >= maxSelfX) {
            return SpaceIntersectAndDistance(false, minOtherX - maxSelfX);

        } else {
            if (minOtherX >= minSelfX && maxOtherX <= maxSelfX) {        // Other is inside self or equal
                overlappingDistanceX = fmin(maxSelfX-minOtherX, maxOtherX-minSelfX);

            } else if (minSelfX >= minOtherX && maxSelfX <= maxOtherX) { // Self is inside other or equal
                overlappingDistanceX = fmin(maxOtherX-minSelfX, maxSelfX-minOtherX);

            } else if (minOtherX <= minSelfX && maxOtherX >= minSelfX) { // Other is before self
                overlappingDistanceX = maxOtherX - minSelfX;

            } else if (minSelfX <= minOtherX && maxSelfX >= minOtherX) { // Self is before other
                overlappingDistanceX = maxSelfX - minOtherX;
            }
        }

        double minSelfY = 0, maxSelfY = 0,
                minOtherY = 0, maxOtherY = 0,
                overlappingDistanceY = 0;

        SpaceLine line2 = SpaceLine(this->bottomRight(), this->bottomLeft()).normalWithPoint(this->bottomLeft());

        double valueBottom = line2.valueOnLine(this->bottomRight());
        double valueTop = line2.valueOnLine(this->topRight());

        minSelfY = fmin(valueBottom, valueTop);
        maxSelfY = fmax(valueBottom, valueTop);

        minOtherY = fmin(
                fmin( line2.valueOnLine(other.bottomLeft()), line2.valueOnLine(other.bottomRight()) ),
                fmin( line2.valueOnLine(other.topLeft()),    line2.valueOnLine(other.topRight())    )
        );

        maxOtherY = fmax(
                fmax( line2.valueOnLine(other.bottomLeft()), line2.valueOnLine(other.bottomRight()) ),
                fmax( line2.valueOnLine(other.topLeft()),    line2.valueOnLine(other.topRight())    )
        );

        if (minOtherY <= minSelfY && maxOtherY <= minSelfY) {
            return SpaceIntersectAndDistance(false, minSelfY - maxOtherY);

        } else if (maxOtherY >= maxSelfY && minOtherY >= maxSelfY) {
            return SpaceIntersectAndDistance(false, minOtherY - maxSelfY);

        } else {

            if (minOtherY >= minSelfY && maxOtherY <= maxSelfY) {        // Other is inside self or equal
                overlappingDistanceY = fmin(maxSelfY-minOtherY, maxOtherY-minSelfY);

            } else if (minSelfY >= minOtherY && maxSelfY <= maxOtherY) { // Self is inside other or equal
                overlappingDistanceY = fmin(maxOtherY-minSelfY, maxSelfY-minOtherY);

            } else if (minOtherY <= minSelfY && maxOtherY >= minSelfY) { // Other is before self
                overlappingDistanceY = maxOtherY - minSelfY;

            } else if (minSelfY <= minOtherY && maxSelfY >= minOtherY) { // Self is before other
                overlappingDistanceY = maxSelfY - minOtherY;
            }

            return SpaceIntersectAndDistance(true, overlappingDistanceX, overlappingDistanceY);
        }

    } else {
        return SpaceIntersectAndDistance(false, centerDistance - (radiusSelf + radiusOther));
    }
}
