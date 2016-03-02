
//https://wiki.libsdl.org/SDL_CreateRGBSurface
//https://wiki.libsdl.org/SDL_FillRect

#include "EngineWorld.h"

EngineWorld::EngineWorld(int r, int g, int b):_items() {
	this->_backgroundImage = SDL_CreateRGBSurface(0, 1, 1, 32, 0,0,0,0);
	SDL_FillRect(this->_backgroundImage, NULL, SDL_MapRGB(this->_backgroundImage->format, r, g, b));
}

EngineWorld::EngineWorld(std::string* backgroundImageFile):_items() {
	this->_backgroundImage = IMG_Load(backgroundImageFile->c_str());

	if (this->_backgroundImage == NULL) {
		std::cout << "IMG_Load failed :" << IMG_GetError() << std::endl;
	}
}

/* When attached/detached to engine */

void EngineWorld::attachedToEngineWithRenderer(SDL_Renderer* renderer) {
	this->_renderer = renderer;
	this->createTexturesWithEngineItems();
}

void EngineWorld::detachedFromEngine() {
	this->_renderer = NULL;
	this->wipeTexturesFromEngineItems();
}

void EngineWorld::createTexturesWithEngineItems() {
	
}

void EngineWorld::wipeTexturesFromEngineItems() {

}

void EngineWorld::addItem(EngineItem* item) {
	this->_items.push_back(item);
	if (this->_renderer != NULL) {

	}
}