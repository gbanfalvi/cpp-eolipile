
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

#include "EngineItemState.h"
#include "EngineDimension.h"

class EngineItem {
private:
	EngineDimensions _dimensions;

	std::map<std::string, EngineItemState> 	* _states;
	std::string 							* _currentItemStateName;
	EngineItemState 						* _currentItemState;

public:
	EngineItem();

	/* Item states */

	void addState(EngineItemState state);
	bool setState(std::string *stateName);


	void cleanUp();

	~EngineItem();
};

#endif