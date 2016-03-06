
/** 
Kinda wanted to do animations and have different states (e.g running, jumping, etc) for my sprites, 
and I realized that it'd be a bit more complex than I thought. 

The basic class for all in-game objects is EngineItem, everything that is displayed is one.

EngineItems can be one of three types that have special properties and determine how the engine 
deals with them:

	- MovingEngineItem: Will update its location relative to the world every frame (e.g. a 
	  character, powerup)

	- FixedEngineItem: Stands fixed throughout the entirety of the playthrough in the foreground 
	  (e.g. ground or walls)

	- BackgroundEngineItem: Stands fixed throughout the entirety of the playthrough in the 
	  background (e.g a bush or a cloud).

	If a MovingEngineItem collides with another MovingEngineItem or a FixedEngineItem, its member
	function: collidedWith() is called.

*/

#ifndef _INCL_ENGINE_ITEM_H

#define _INCL_ENGINE_ITEM_H

#include <map>
#include <string>
#include <cmath>

#include "SDLLibs.hpp"
#include "Geometry.hpp"
#include "EngineDimensions.hpp"

class EngineItemState;
class EngineWorld;

#define IGNORE_VALUE NAN


class EngineItem : public Positioned {
private:
    
	EngineDimensions _dimensions;

	std::map<std::string, EngineItemState *> * _states;
	std::string 							 * _currentItemStateName;
	EngineItemState 						 * _currentItemState;
    EngineWorld                              * _currentAttachedWorld;
    
    // Private setters
    
    bool _setPosX(double x);
    bool _setPosY(double y);
    bool _setWidth(double width);
    bool _setHeight(double height);
    bool _setRotation(double rot);
    
    void _dimensionsChanged();

public:

    // Constructors
    
    inline EngineItem(double x, double y, double w, double h):_dimensions(x, y, w, h) {
        _states = new std::map<std::string, EngineItemState*>();
    };
    
    inline EngineItem():_dimensions(0, 0, 0, 0) {
        _states = new std::map<std::string, EngineItemState*>();
    };
    
    inline EngineItem(const EngineItem& item, bool copyDimensions, bool copyStates) {
        
        if (copyDimensions) {
            _dimensions = EngineDimensions(item._dimensions);
        }
        
        if (copyStates) {
            _states = item._states;
        } else {
            _states = new std::map<std::string, EngineItemState*>();
        }
    }
    
    // Events
    
    void attachedToWorld(EngineWorld *world);
    
    void detachedFromWorld();
    
    // Sprite

    // Setters
    
    void setDimensions(double x, double y, double w, double h) {
        bool dimensionsChanged = _setPosX(x) || _setPosY(y) || _setWidth(w) || _setHeight(h);
        if (dimensionsChanged) _dimensionsChanged();
    }
    
    void setSize(double w, double h) {
        bool dimensionsChanged = _setWidth(w) || _setHeight(h);
        if (dimensionsChanged) _dimensionsChanged();
    }
    
    void setPosition(double x, double y) {
        bool dimensionsChanged = _setPosX(x) || _setPosY(y);
        if (dimensionsChanged) _dimensionsChanged();
    }
    
    void setRotation(double rot) {
        if (_setRotation(rot)) _dimensionsChanged();
    }
    
    inline void setFlip(ItemFlip flip) {
        _dimensions.flip = flip;
    }
    
	void addState(EngineItemState *state);
	bool setState(std::string stateName);
    
    // Getters
    
    inline double getPosX() const {
        return _dimensions.origin.x;
    }
    
    inline double getPosY() const {
        return _dimensions.origin.y;
    }
    
    inline double getWidth() const {
        return _dimensions.size.width;
    }
    
    inline double getSize() const {
        return _dimensions.size.height;
    }
    
    inline double getRotation() const {
        return _dimensions.rotation;
    }
    
    inline ItemFlip getFlip() const {
        return _dimensions.flip;
    }
    
    inline Rect getLocation() const {
        return _dimensions;
    }

	void cleanUp();

	~EngineItem();
};

#endif