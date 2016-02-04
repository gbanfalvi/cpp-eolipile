
/**

Implementation details:

Unfortunately, as a constraint of the game engine (to make it as neat and simple as possible), each 
EngineSprite (and thus each EngineItem and EngineWorld) is constrained to a single renderer at a 
time. You can't run it in more than one window at once.

Once you put an EngineSprite in an EngineItemState, an EngineItemState in an EngineItem, an 
EngineItem in an EngineWorld and an EngineWorld on an Engine, the sprite's textures are generated
so that they're immediately consumable by the renderer in the Engine. 

Interesting library documentation:

https://wiki.libsdl.org/SDL_RenderCopy
https://wiki.libsdl.org/SDL_CreateTextureFromSurface

TODO: 

- Switch to this in render() ASAP: https://wiki.libsdl.org/SDL_RenderCopyEx
- Should I destroy the surface as soon as I have a texture? I don't think I need it anymore.

*/

#include "EngineSprite.h"

#include <iostream>
#include <string>

EngineSprite::EngineSprite(std::string *filename) {
	this->_filename = filename;
	this->_image = IMG_Load(filename->c_str());

	if (this->_image == NULL) {
		std::cout << "IMG_Load failed :" << IMG_GetError() << std::endl;
	}
}

EngineSprite::~EngineSprite() {
	if (this->_image != NULL) {
		SDL_FreeSurface(this->_image);
	}

	if (this->_texture != NULL) {
		SDL_DestroyTexture(this->_texture);
	}

	delete this->_filename;
}

int EngineSprite::getWidth() {
	return this->_image->w;
}

int EngineSprite::getHeight() {
	return this->_image->h;
}

bool EngineSprite::isLoaded() {
	return this->_image != NULL;
}

void EngineSprite::createTexture(SDL_Renderer* renderer) {
	this->_texture = SDL_CreateTextureFromSurface(renderer, this->_image);

	if (this->_texture == NULL) {
    	std::cout << "CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
    }
}

void EngineSprite::render(int x, int y, int w, int h, SDL_Renderer* renderer) {
	SDL_Rect location;
	location.x = x;
	location.y = y;
	location.w = w;
	location.h = h;

	SDL_RenderCopy(renderer, this->_texture, NULL, &location);
}

