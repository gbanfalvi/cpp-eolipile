/**
 * Basic type that subclasses Rect from the geometry library and supports a few new copy
 * constructors.
 *
 * If you need any of the other default constructors, you might have to override them here.
 */

#ifndef EngineDimensions_hpp
#define EngineDimensions_hpp

#include <stdio.h>
#include "SDLLibs.hpp"
#include "Geometry.hpp"

typedef SDL_RendererFlip ItemFlip;

const ItemFlip ItemFlipHorizontal = SDL_FLIP_HORIZONTAL;
const ItemFlip ItemFlipVertical   = SDL_FLIP_VERTICAL;
const ItemFlip ItemFlipNone 	  = SDL_FLIP_NONE;

struct EngineDimensions : public Rect {
    ItemFlip flip;
    
    EngineDimensions() {};
    
    EngineDimensions(double x, double y, double w, double h): Rect(x, y, w, h) {}
    
    EngineDimensions(const EngineDimensions& dimensions): Rect(dimensions), flip(dimensions.flip) {}
    
    EngineDimensions(const EngineDimensions& dimensions, bool copyFlip): Rect(dimensions) {
        if (copyFlip) {
            flip = dimensions.flip;
        }
    }
};

#endif /* EngineDimensions_hpp */
