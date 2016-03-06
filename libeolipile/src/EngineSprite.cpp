
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

#include "EngineSprite.hpp"
#include "EngineDimensions.hpp"

#include <iostream>
#include <string>

EngineSprite::EngineSprite(std::string *filename) {
	_filename = filename;
	_image = IMG_Load(filename->c_str());

	if (_image == NULL) {
		std::cout << "IMG_Load failed :" << IMG_GetError() << std::endl;
	}
}

EngineSprite::~EngineSprite() {
	if (_image != NULL) {
		SDL_FreeSurface(_image);
	}

	if (_texture != NULL) {
		SDL_DestroyTexture(_texture);
	}

	delete _filename;
}

int EngineSprite::getWidth() {
	return _image->w;
}

int EngineSprite::getHeight() {
	return _image->h;
}

bool EngineSprite::isLoaded() {
	return _image != NULL;
}

void EngineSprite::createTexture(SDL_Renderer* renderer) {
	_texture = SDL_CreateTextureFromSurface(renderer, _image);

	if (_texture == NULL) {
    	std::cout << "CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
    }
}

void EngineSprite::render(int x, int y, int w, int h, SDL_Renderer* renderer) {
	SDL_Rect location;
	location.x = x;
	location.y = y;
	location.w = w;
	location.h = h;

	SDL_RenderCopy(renderer, _texture, NULL, &location);
}

