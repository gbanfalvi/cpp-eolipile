//
//  SpatialHash.cpp
//  lib-geometry
//
//  Created by Gabriel Banfalvi on 09/02/16.
//
//

#include "SpatialHash.hpp"

#include "Point.hpp"
#include "Rect.hpp"
#include "Size.hpp"

std::vector<SpaceCell*> SpatialHash::matchingCells(Rect location, bool createIfNotExists) {
    int minX = location.minX() / _cellSize;
    int maxX = location.maxX() / _cellSize;
    
    int minY = location.minY() / _cellSize;
    int maxY = location.maxY() / _cellSize;
    
    int diffX = maxX - minX > 0 ? maxX - minX : 1;
    int diffY = maxY - minY > 0 ? maxY - minY : 1;
    
    std::vector<SpaceCell*> cells{};
    
    for (int x = 0; x < diffX; x++) {
        for (int y = 0; y < diffY; y++) {
            Point searchPoint = Point(minX + x, minY + y);
            
            std::map<Point, SpaceCell, PointCompare>::iterator search = _pointToCell.find(searchPoint);
            
            if (search != _pointToCell.end()) {
                cells.push_back(&search->second);
            
            } else if (createIfNotExists) {
                SpaceCell newCell = SpaceCell();
                std::pair<std::map<Point, SpaceCell, PointCompare>::iterator, bool> location = _pointToCell.insert(std::pair<Point, SpaceCell>(searchPoint, newCell));
                cells.push_back(&location.first->second);
            }
        }
    }
    
    return cells;
}

void SpatialHash::add(Positioned *item) {
    
    std::vector<SpaceCell*> cells = matchingCells(item->getLocation(), true);
    
    for (SpaceCell* cell : cells) {
        cell->items.push_back(item);
    }
}

void SpatialHash::remove(Positioned *item) {

    std::vector<SpaceCell*> cells = matchingCells(item->getLocation(), false);
    
    for (SpaceCell* cell : cells) {
        std::vector<Positioned*>* items = &cell->items;
        
        std::vector<Positioned*>::iterator result = std::find(items->begin(), items->end(), item);
        
        if (result != items->end()) {
            items->erase(result);
        }
    }
}

void SpatialHash::move(Positioned *item, Rect previousLocation) {
    
    std::vector<SpaceCell*> previousCells = matchingCells(previousLocation, false);
    std::vector<SpaceCell*> newCells = matchingCells(item->getLocation(), true);
    
    for (SpaceCell *newCell : newCells) {
        std::vector<Positioned*>::iterator newCellLocation = std::find(newCell->items.begin(), newCell->items.end(), item);
        
        if (newCellLocation != newCell->items.end()) {
            std::vector<SpaceCell*>::iterator prevLocation = std::find(previousCells.begin(), previousCells.end(), newCell);
            
            if (prevLocation != previousCells.end()) {
                previousCells.erase(prevLocation);
            }
            
        } else {
            newCell->items.push_back(item);
        }
    }
    
    for (SpaceCell *prevCell : previousCells) {
        std::vector<Positioned*>::iterator itemLocation = std::find(prevCell->items.begin(), prevCell->items.end(), item);
        if (itemLocation != prevCell->items.end()) {
            prevCell->items.erase(itemLocation);
        }
    }
}

std::vector<Positioned *> SpatialHash::intersections(Rect location, bool evaluateAllItems) {
    std::vector<Positioned *> intersectedItems{};
    
    std::vector<SpaceCell*> cells = matchingCells(location, false);
    
    for (SpaceCell *cell : cells) {
        for (Positioned *item : cell->items) {
            if (item->isIntersectedByOthers() || evaluateAllItems) {
                if (item->getLocation().intersects(location).intersects) {
                    intersectedItems.push_back(item);
                }
            }
        }
    }
    
    return intersectedItems;
}



