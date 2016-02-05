
/**

EngineSprite

This represents a single in-game sprite. This object just wraps an SDL_Surface and an SDL_Texture
and destroys them when the sprite is deleted.

*/

#ifndef _INCL_ENGINE_SPRITE_H
#define _INCL_ENGINE_SPRITE_H

#include "SDLLibs.h"
#include <string>


class EngineSprite {
private:
	SDL_Surface *_image;
	SDL_Texture *_texture;

	std::string *_filename;

public:

	EngineSprite(std::string *filename);

	~EngineSprite();

	int getWidth() ;
	int getHeight();

	bool isLoaded();

	void createTexture(SDL_Renderer* renderer);
	void render(int x, int y, int w, int h, SDL_Renderer* renderer);
};

#endif