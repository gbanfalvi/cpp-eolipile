
#include "EngineItem.hpp"
#include "EngineWorld.hpp"
#include "EngineItemState.hpp"

/* Private setters */


inline bool EngineItem::_setPosX(double x) {
    if (x != IGNORE_VALUE && _dimensions.origin.x != x) {
        _dimensions.origin.x = x;
        return true;
    } else {
        return false;
    }
}

inline bool EngineItem::_setPosY(double y) {
    if (y != IGNORE_VALUE && _dimensions.origin.y != y) {
        _dimensions.origin.y = y;
        return true;
    } else {
        return false;
    }
}

inline bool EngineItem::_setWidth(double width) {
    if (width != IGNORE_VALUE && _dimensions.size.width != width) {
        _dimensions.size.width = width;
        return true;
    } else {
        return false;
    }
}

inline bool EngineItem::_setHeight(double height) {
    if (height != IGNORE_VALUE && _dimensions.size.height != height) {
        _dimensions.size.height = height;
        return true;
    } else {
        return false;
    }
}

inline bool EngineItem::_setRotation(double rot) {
    if (rot != IGNORE_VALUE && _dimensions.rotation != rot) {
        _dimensions.rotation = rot;
        return true;
    } else {
        return false;
    }
}

// Events

void EngineItem::attachedToWorld(EngineWorld *world) {
    if (_currentAttachedWorld != NULL) {
        detachedFromWorld();
    }
    
    _currentAttachedWorld = world;
}


/* Constructors */


/* Item states */

void EngineItem::addState(EngineItemState *state) {
	_states->insert(std::pair<std::string, EngineItemState *>(*state->getName(), state));
}

bool EngineItem::setState(std::string stateName) {
	std::map<std::string, EngineItemState *>::iterator it;
	it = _states->find(stateName);

	if (it == _states->end()) {
		return false;
	} else {
		_currentItemStateName = it->second->getName();
		_currentItemState = it->second;
		return true;
	}
}

void EngineItem::detachedFromWorld() {
    
}

