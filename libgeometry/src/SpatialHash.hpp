//
//  SpatialHash.hpp
//  lib-geometry
//
//  Created by Gabriel Banfalvi on 09/02/16.
//
//

#ifndef SpatialHash_hpp
#define SpatialHash_hpp

#include <vector>
#include <map>
#include <cmath>
#include <utility> //pair

#include "Point.hpp"

struct Rect;

class Positioned {
public:
    virtual Rect getLocation() const;
    virtual bool isIntersectedByOthers() const;
    virtual bool intersectsOthers() const;
};

struct SpaceCell {
    std::vector<Positioned*> items;
};

class SpatialHash {
private:
    int _cellSize;
    std::map<Point, SpaceCell, PointCompare> _pointToCell;
    
    std::vector<SpaceCell*> matchingCells(Rect location, bool createIfNotExists);

public:
    SpatialHash(int cellSize): _cellSize(cellSize){};
    ~SpatialHash(){};
    
    void add(Positioned *item);
    void remove(Positioned *item);
    void move(Positioned *item, Rect previousLocation);
    std::vector<Positioned *> intersections(Rect location, bool evaluateAllItems);
    
};

#endif /* SpatialHash_hpp */
