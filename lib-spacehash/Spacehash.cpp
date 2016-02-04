//
// Created by Gabriel Banfalvi on 01/02/16.
//

#include "Spacehash.h"

void SpaceHash::add(Positioned *item) {
    int minX = item->getLocation().origin.x / _cellSize;
    int maxX = (item->getLocation().origin.x + item->getLocation().size.width) / _cellSize;

    int minY = item->getLocation().origin.y / _cellSize;
    int maxY = (item->getLocation().origin.y + item->getLocation().size.height) / _cellSize;

    int diffX = maxX - minX > 0 ? maxX - minX : 1;
    int diffY = maxY - minY > 0 ? maxY - minY : 1;

    std::vector<SpacePoint> points(diffX * diffY);

    // Unifinished
}
