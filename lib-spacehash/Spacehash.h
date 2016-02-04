//
// Created by Gabriel Banfalvi on 01/02/16.
//

#ifndef EOLIPILE_SPACEHASH_H
#define EOLIPILE_SPACEHASH_H

#include <vector>
#include <map>
#include <cmath>
#include <utility> //pair

#include "SpaceStructs.h"

class Positioned {
public:
    virtual SpaceRect getLocation() const;
};

struct SpaceCell {
    std::vector<Positioned*> items;
};

class SpaceHash {
private:
    int _cellSize;
    std::map<SpacePoint, SpaceCell, SpacePointCompare> _pointToCell;
public:
    SpaceHash(int cellSize): _cellSize(cellSize){};
    ~SpaceHash();

    void add(Positioned *item);
    void remove(Positioned *item);
    void move(Positioned *item, SpaceRect previousLocation);
    std::vector<Positioned *> intersections(Positioned *item);
};

#endif //EOLIPILE_SPACEHASH_H
