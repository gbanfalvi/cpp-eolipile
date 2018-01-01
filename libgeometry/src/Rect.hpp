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

/// SpaceIntersectAndDistance describes the intersection and overlap of two rectangles (roughly)
struct SpaceIntersectAndDistance {
    /// True if two `Rect`s intersect
    bool intersects;

    /// Rough estimate of how far two non-intersecting `Rect`s are from each other (regardless of rotation)
    double distance;

    /// Size of overlap if two `Rect`s intersect, relative to the orientation of the callee.
    Size overlapSize;
    
    SpaceIntersectAndDistance(bool intersects, double distance)
    :intersects(intersects), distance(distance), overlapSize(0,0){};
    
    SpaceIntersectAndDistance(bool intersects, double overlapX, double overlapY)
    :intersects(intersects), distance(0), overlapSize(overlapX,overlapY){};
};

/// Rectangle object
struct Rect {

    /// Top left point
    Point origin;
    /// Size
    Size size;
    /// Rotation in radians
    double rotation;

    /// Rectangle at 0,0 with size 0x0 and rotation 0
    Rect() {};

    /// Rectangle with provided origin coords, dimensions and rotation
    /// \param x origin x
    /// \param y origin y
    /// \param width rect width
    /// \param height rect height
    /// \param rotation rotation in radians
    Rect(double x, double y, double width, double height, double rotation): origin(x, y), size(width, height), rotation(rotation) {};

    /// Rectangle with origin point, size and rotation
    /// \param origin origin point
    /// \param size size
    /// \param rotation rotation
    Rect(Point origin, Size size, double rotation): origin(origin), size(size), rotation(rotation) {};

    /// Rectangle with origin coords and dimensions. Rotation is zero
    /// \param x origin x
    /// \param y origin y
    /// \param width rect width
    /// \param height rect height
    Rect(double x, double y, double width, double height): origin(x, y), size(width, height), rotation(0) {};

    /// Rectangle with origin point and size. Rotation is zero.
    ///
    /// \param origin origin point
    /// \param size size
    Rect(Point origin, Size size): origin(origin), size(size), rotation(0) {};

    /// Copy constructor
    /// \param r
    Rect(const Rect& r):origin(r.origin), size(r.size), rotation(r.rotation) {};

    /// Determines if a Rect overlaps another one and either how much distance remains or the overlap depth in X and Y
    /// \param other
    /// \return whether it overlaps or not and by how much
    SpaceIntersectAndDistance intersects(const Rect& other) const;

    /// Center of rectangle
    /// \return center point
    inline Point center() const {
        
        return Point(origin.x + size.width/2,
                     origin.y - size.height/2);
    }

    /// Rotated X-component
    /// \param unrotatedSource source point whose X component is rotated around center
    /// \return position of X component once rotated around center by rectangle's rotation
    inline double rotatedX(Point unrotatedSource) const {
        return center().x +
        cos(rotation) * (unrotatedSource.x - center().x) -
        sin(rotation) * (unrotatedSource.y - center().y);
    }

    /// Rotated Y-component
    /// \param unrotatedSource source point whose Y compoennt is rotated around center
    /// \return position of Y component once rotated around center by rectangle's rotation
    inline double rotatedY(Point unrotatedSource) const {
        return center().y +
        sin(rotation) * (unrotatedSource.x - center().x) +
        cos(rotation) * (unrotatedSource.y - center().y);
    }

    /// Rotated point
    /// \param unrotatedSource source point
    /// \return position of point once rotated around center by rectangle's rotation
    inline Point rotatedPoint(Point unrotatedSource) const {
        return Point(rotatedX(unrotatedSource), rotatedY(unrotatedSource));
    }

    /// Length of rect from one corner to diagonal opposite
    /// \return
    inline double diagonalLength() const {
        return  sqrt(pow(size.width, 2) + pow(size.height, 2));
    }

    /// Top left corner's position after applying rotation
    /// \return
    inline Point topLeft() const {
        return rotatedPoint(origin);
    }

    /// Top right corner's position after applying rotation
    inline Point topRight() const {
        return rotatedPoint(Point(origin.x + size.width, origin.y));
    }

    /// Bottom left corner's position after applying rotation
    inline Point bottomLeft() const {
        return rotatedPoint(Point(origin.x, origin.y - size.height));
    }

    /// Bottom right corner's position after applying rotation
    inline Point bottomRight() const {
        return rotatedPoint(Point(origin.x + size.width, origin.y - size.height));
    }

    /// Smallest X position of any corner once rotated
    /// \return
    inline double minX() const {
        return fmin(fmin(rotatedX(origin),
                         rotatedX(Point(origin.x + size.width, origin.y))),
                    fmin(rotatedX(Point(origin.x, origin.y - size.height)),
                         rotatedX(Point(origin.x + size.width, origin.y - size.height)))
                    );
    }

    /// Smallest Y position of any corner once rotated
    /// \return
    inline double minY() const {
        return fmin(fmin(rotatedY(origin),
                         rotatedY(Point(origin.x + size.width, origin.y))),
                    fmin(rotatedY(Point(origin.x, origin.y - size.height)),
                         rotatedY(Point(origin.x + size.width, origin.y - size.height)))
                    );
    }

    /// Largest X position of any corner once rotated
    inline double maxX() const {
        return fmax(fmax(rotatedX(origin),
                         rotatedX(Point(origin.x + size.width, origin.y))),
                    fmax(rotatedX(Point(origin.x, origin.y - size.height)),
                         rotatedX(Point(origin.x + size.width, origin.y - size.height)))
                    );
    }

    /// Latgest Y position of any corner once rotated
    inline double maxY() const {
        return fmax(fmax(rotatedY(origin),
                         rotatedY(Point(origin.x + size.width, origin.y))),
                    fmax(rotatedY(Point(origin.x, origin.y - size.height)),
                         rotatedY(Point(origin.x + size.width, origin.y - size.height)))
                    );
    }

};

std::ostream &operator<< (std::ostream &os, Rect const &rect);

#endif /* Rect_hpp */
