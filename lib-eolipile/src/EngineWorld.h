
/**

An engine world is a collection of all GameItems in a game for e.g. a level. The general process to 
get it all working is:

	- Add/remove items to the world.
	- Move the world camera around.
*/

#ifndef _INCL_ENGINE_MAP_H
#define _INCL_ENGINE_MAP_H

#import <vector>
#import <string>
#import <iostream>

#ifdef MACOSX
	#import <SDL2/SDL.h>
	#import <SDL2_image/SDL_image.h>
#endif

#import "EngineItem.h"

class EngineWorld {
private: 
	SDL_Texture *_backgroundTexture;
	SDL_Surface *_backgroundImage;

	std::vector<EngineItem*> _items;

	int cam_pos_x;
	int cam_pos_y;

	int cam_width;
	int cam_height;
	
	int cam_scale;

	SDL_Renderer* _renderer;

	void createTexturesWithEngineItems();
	void wipeTexturesFromEngineItems();

public:
	/** Initialize a world with a specific background color. Values from 0-255 */
	EngineWorld(int r, int g, int b);

	/** Initialize a world with a specific background image from res. EngineWorld doesn't own 
	the image filename, delete it yourself when done */
	EngineWorld(std::string* backgroundImageFile);

	/** Add a single EngineItem. EngineWorld doesn't own it (delete yourself when done) */
	void addItem(EngineItem* item);

	/** Remove this single item. Remember to delete it when you don't need it. */
	void removeItem(EngineItem* item);

	/** Remove all items from EngineWorld. Rememebr to delete them yourself. */
	void removeAllItems();

	void renderFrame();

	/** Called when an EngineWorld is attached to the engine. You don't need to call this 
	yourself. Used to generate textures on the graphics card for all EngineItem sprites */
	void attachedToEngineWithRenderer(SDL_Renderer* renderer);

	/** Called when an engine world is replaced on an Engine. You don't need to call this 
	yourself. */
	void detachedFromEngine();

	//TODO: Add methods to shift cam properties.


	void cleanUp();

	~EngineWorld();
};



#endif