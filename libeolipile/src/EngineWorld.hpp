
/**

An engine world is a collection of all GameItems in a game for e.g. a level. The general process to 
get it all working is:

	- Add/remove items to the world.
	- Move the world camera around.
*/

#ifndef _INCL_ENGINE_MAP_H
#define _INCL_ENGINE_MAP_H

#include <vector>
#include <string>
#include <iostream>

#include "SDLLibs.hpp"
#include "Geometry.hpp"

class EngineItem;

class EngineWorld {
private: 
	SDL_Texture *_backgroundTexture;
	SDL_Surface *_backgroundImage;

	std::vector<EngineItem*> _items;
    SpatialHash _worldMap;

    Rect camera{0, 0, 640, 480};

	SDL_Renderer* _renderer;

	void createTexturesWithEngineItems(); // WIP
	void wipeTexturesFromEngineItems(); // WIP
    
public:
	
    EngineWorld(int r, int g, int b); // DONE
    EngineWorld(std::string* backgroundImageFile); // DONE

	void addItem(EngineItem* item); // WIP
    void removeItem(EngineItem* item); // WIP
    void removeAllItems(); // WIP

	void renderFrame(); // WIP

	void attachedToEngineWithRenderer(SDL_Renderer* renderer); // DONE
    void detachedFromEngine(); // DONE
    void itemMoved(EngineItem *item, Rect previousLocation);

	//TODO: Add methods to shift cam properties.

	void cleanUp(); // WIP
    ~EngineWorld(); // WIP
};



#endif