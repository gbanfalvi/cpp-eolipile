
//https://wiki.libsdl.org/SDL_CreateRGBSurface
//https://wiki.libsdl.org/SDL_FillRect

#include "EngineWorld.hpp"
#include "EngineItem.hpp"

EngineWorld::EngineWorld(int r, int g, int b):_items(), _worldMap(20) {
	_backgroundImage = SDL_CreateRGBSurface(0, 1, 1, 32, 0,0,0,0);
	SDL_FillRect(_backgroundImage, NULL, SDL_MapRGB(_backgroundImage->format, r, g, b));
}

EngineWorld::EngineWorld(std::string* backgroundImageFile):_items(), _worldMap(20) {
	_backgroundImage = IMG_Load(backgroundImageFile->c_str());

	if (_backgroundImage == NULL) {
		std::cout << "IMG_Load failed :" << IMG_GetError() << std::endl;
	}
}

/* When attached/detached to engine */

void EngineWorld::attachedToEngineWithRenderer(SDL_Renderer* renderer) {
	_renderer = renderer;
	createTexturesWithEngineItems();
}

void EngineWorld::detachedFromEngine() {
	_renderer = NULL;
	wipeTexturesFromEngineItems();
}

void EngineWorld::createTexturesWithEngineItems() {
	
}

void EngineWorld::wipeTexturesFromEngineItems() {

}

void EngineWorld::addItem(EngineItem* item) {
	_items.push_back(item);
	if (_renderer != NULL) {

	}
}

void EngineWorld::itemMoved(EngineItem *item, Rect previousLocation) {
    _worldMap.move(item, previousLocation);
}