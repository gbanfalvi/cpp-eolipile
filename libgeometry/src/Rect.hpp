//
//  Rect.hpp
//  lib-geometry
//
//  Created by Gabriel Banfalvi on 09/02/16.
//
//

#ifndef Rect_hpp
#define Rect_hpp


#include <cmath>

#include "Size.hpp"
#include "Point.hpp"
#include "Line.hpp"

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
    
    Rect() {};
    Rect(double x, double y, double width, double height, double rotation): origin(x, y), size(width, height), rotation(rotation) {};
    Rect(Point origin, Size size, double rotation): origin(origin), size(size), rotation(rotation) {};
    Rect(double x, double y, double width, double height): origin(x, y), size(width, height), rotation(0) {};
    Rect(Point origin, Size size): origin(origin), size(size), rotation(0) {};
    
    Rect(const Rect& r):origin(r.origin), size(r.size), rotation(r.rotation) {};
    
    /**
     * Determines if a SpaceRect overlaps another SpaceRect and either how much distance remains or overlap depth
     * returns a SpaceIntersectAndDistance
     */
    SpaceIntersectAndDistance intersects(const Rect& other) const;
    
    inline Point center() const {
        
        return Point(origin.x + size.width/2,
                     origin.y - size.height/2);
    }
    
    inline double rotatedX(Point unrotatedSource) const {
        return center().x +
        cos(rotation) * (unrotatedSource.x - center().x) -
        sin(rotation) * (unrotatedSource.y - center().y);
    }
    
    inline double rotatedY(Point unrotatedSource) const {
        return center().y +
        sin(rotation) * (unrotatedSource.x - center().x) +
        cos(rotation) * (unrotatedSource.y - center().y);
        
    }
    
    inline Point rotatedPoint(Point unrotatedSource) const {
        return Point(rotatedX(unrotatedSource), rotatedY(unrotatedSource));
    }
    
    inline double diagonalLength() const {
        return  sqrt(pow(size.width, 2) + pow(size.height, 2));
    }
    
    inline Point topLeft() const {
        return rotatedPoint(origin);
    }
    
    inline Point topRight() const {
        return rotatedPoint(Point(origin.x + size.width, origin.y));
    }
    
    inline Point bottomLeft() const {
        return rotatedPoint(Point(origin.x, origin.y - size.height));
    }
    
    inline Point bottomRight() const {
        return rotatedPoint(Point(origin.x + size.width, origin.y - size.height));
    }
    
    inline double minX() const {
        return fmin(fmin(rotatedX(origin),
                         rotatedX(Point(origin.x + size.width, origin.y))),
                    fmin(rotatedX(Point(origin.x, origin.y - size.height)),
                         rotatedX(Point(origin.x + size.width, origin.y - size.height)))
                    );
    }
    
    inline double minY() const {
        return fmin(fmin(rotatedY(origin),
                         rotatedY(Point(origin.x + size.width, origin.y))),
                    fmin(rotatedY(Point(origin.x, origin.y - size.height)),
                         rotatedY(Point(origin.x + size.width, origin.y - size.height)))
                    );
    }
    
    inline double maxX() const {
        return fmax(fmax(rotatedX(origin),
                         rotatedX(Point(origin.x + size.width, origin.y))),
                    fmax(rotatedX(Point(origin.x, origin.y - size.height)),
                         rotatedX(Point(origin.x + size.width, origin.y - size.height)))
                    );
    }
    
    inline double maxY() const {
        return fmax(fmax(rotatedY(origin),
                         rotatedY(Point(origin.x + size.width, origin.y))),
                    fmax(rotatedY(Point(origin.x, origin.y - size.height)),
                         rotatedY(Point(origin.x + size.width, origin.y - size.height)))
                    );
    }
    
};

#endif /* Rect_hpp */
