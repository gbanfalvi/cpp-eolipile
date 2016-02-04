
/**

EngineItemState

An EngineItemState is one of the many "states" or animation cycles an EngineItem can be in. 
E.g. a character could be running, standing still, jumping, etc.

This object contains a collection of one or more EngineSprites. This is to abstract away animations
from EngineItem.

Thinking later of adding other attributes to this class like a framerate; so each state can run its
animation cycle at different speeds.

*/

#ifndef _INCL_ENGINE_ITEM_STATE_H

#define _INCL_ENGINE_ITEM_STATE_H

#import <vector>
#import <string>
#import "EngineSprite.h"

class EngineItemState {
private:
	std::string *				_stateName;
	int 						_stateFramesPerSprite;
	std::vector<EngineSprite> 	_sprites;

public:
	EngineItemState(std::string* name, int framesPerSprite, EngineSprite n_sprites, ...);
	~EngineItemState();

	std::string * getName();

	void enabledState();
	void render(int x, int y, int w, int h, SDL_Renderer *renderer);
};

#endif