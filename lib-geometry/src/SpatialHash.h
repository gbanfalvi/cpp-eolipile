//
// Created by Gabriel Banfalvi on 04/02/16.
//

#ifndef EOLIPILE_SPATIALHASH_H
#define EOLIPILE_SPATIALHASH_H

#include <vector>
#include <map>
#include <cmath>
#include <utility> //pair

#include "Point.h"
#include "Rect.h"

class Positioned {
public:
    virtual Rect getLocation() const;
};

struct SpaceCell {
    std::vector<Positioned*> items;
};

class SpatialHash {
private:
    int _cellSize;
    std::map<Point, SpaceCell, PointCompare> _pointToCell;
public:
    SpatialHash(int cellSize): _cellSize(cellSize){};
    ~SpatialHash();

    void add(Positioned *item);
    void remove(Positioned *item);
    void move(Positioned *item, Rect previousLocation);
    std::vector<Positioned *> intersections(Positioned *item);
};

#endif //EOLIPILE_SPATIALHASH_H
