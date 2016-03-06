
#include "EngineItemState.hpp"

#include "EngineSprite.hpp"

EngineItemState::EngineItemState(std::string *name, int framesPerSprite, EngineSprite n_sprites, ...) {
	_stateName = name;
	_sprites = std::vector<EngineSprite>();
	_stateFramesPerSprite = framesPerSprite;
}

std::string * EngineItemState::getName() {
	return  _stateName;
}

void EngineItemState::render(EngineDimensions *dimensions, SDL_Renderer *renderer) {
    
}
EngineItemState::~EngineItemState() {
}