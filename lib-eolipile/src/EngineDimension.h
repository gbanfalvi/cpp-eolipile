
#ifndef _INCL_ENGINE_DIM_H
#define _INCL_ENGINE_DIM_H

#ifdef MACOSX
	#import <SDL2/SDL.h>
	#import <SDL2_image/SDL_image.h>

#endif

/**
	ItemFlip is an attempt at absctracting away the flip from SDL. 
	
	If you want to flip something both horizontally and vertically, you can do:
	item.dimensions.flip = ItemFlipHorizontal | ItemFlipVertical

	Docs:

	https://wiki.libsdl.org/SDL_RendererFlip
*/

typedef SDL_RendererFlip ItemFlip;

const ItemFlip ItemFlipHorizontal = SDL_FLIP_HORIZONTAL;
const ItemFlip ItemFlipVertical   = SDL_FLIP_VERTICAL;
const ItemFlip ItemFlipNone 	  = SDL_FLIP_NONE;

/**
	EngineItemDimensions is just a container obejct for positioning/framing of an EngineItem.
*/

struct EngineDimensions {
	int pos_x;
	int pos_y;

	int width;
	int height;

	double rotation;

	ItemFlip flip;

	// These below are all just shortcuts, you can get/set the values dierctly if you want

	void setFrame(int x, int y, int width, int height);
	void setSize(int width, int height);	
	void setPos(int x, int y);

};

#endif