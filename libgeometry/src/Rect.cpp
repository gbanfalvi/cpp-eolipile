//
//  Rect.cpp
//  lib-geometry
//
//  Created by Gabriel Banfalvi on 09/02/16.
//
//

#include "Rect.hpp"

SpaceIntersectAndDistance Rect::intersects(const Rect& other) const {
    double radiusSelf = diagonalLength() / 2;
    double radiusOther = other.diagonalLength() / 2;
    
    Point centerSelf = center();
    Point centerOther = other.center();
    
    double centerDistance = sqrt(pow(centerOther.x - centerSelf.x, 2) + pow(centerOther.y - centerSelf.y, 2));
    
    if (centerDistance <= radiusSelf + radiusOther) {
        
        double minSelfX = 0, maxSelfX = 0,
        minOtherX = 0, maxOtherX = 0,
        overlappingDistanceX = 0;
        
        
        Line line1 = Line(topRight(), bottomRight()).normalWithPoint(bottomRight());
        
        double valueLeft = line1.valueOnLine(bottomLeft());
        double valueRight = line1.valueOnLine(bottomRight());
        
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
        
        Line line2 = Line(bottomRight(), bottomLeft()).normalWithPoint(bottomLeft());
        
        double valueBottom = line2.valueOnLine(bottomRight());
        double valueTop = line2.valueOnLine(topRight());
        
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

std::ostream &operator<< (std::ostream &os, Rect const &rect) {
    os << "Rect <Origin:" << rect.origin << " Size:" << rect.size << " Rotation:" << rect.rotation << ">";
    return os;
}
