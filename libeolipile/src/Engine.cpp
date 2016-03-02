
#include "Engine.h"

/* Initialization */

//Done
Engine::Engine(int w, int h, int fps, std::string *name):_activeKeyboardPresses(), _activeMousePresses() {
	this->_windowWidth = w;
	this->_windowHeight = h;
	this->_windowName = name;
	this->_frameLength = 1000 / fps;
}

//Done
bool Engine::loadWindow() {

	int supportedImageFormats = IMG_INIT_JPG|IMG_INIT_PNG; //SDL supports bmp already

	int loadedImageSupport = IMG_Init(supportedImageFormats);
	if ((loadedImageSupport & supportedImageFormats) != supportedImageFormats) {
		std::cout << "IMG_Init Error: " << IMG_GetError() << std::endl;
		return false;
	}

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	this->_window = SDL_CreateWindow(this->_windowName->c_str(),
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     this->_windowWidth,
                                     this->_windowHeight,
                                     SDL_WINDOW_SHOWN);
	if (this->_window == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		this->cleanUp();
		return false;
	}

	this->_renderer = SDL_CreateRenderer(this->_window,
                                         -1,
                                         SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (_renderer == nullptr){
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		this->cleanUp();
		return false;
	}

	return true;
}

/* Public engine loop functions */

//Done
void Engine::startLoop() {
	this->_loopEnded = false;
	this->_loopPaused = false;

	this->gameLoop();
}

//Done
bool Engine::pauseLoop() {
	this->_loopPaused = !this->_loopPaused;
	return this->_loopPaused;
}

//Done
void Engine::endLoop() {
	this->_loopEnded = true;
}

/* Private engine loop functions */

//WIP
void Engine::gameLoop() {
	
	Uint32 startTicks, endTicks, tickDelta;

	while (this->_loopEnded == false) {
		startTicks = SDL_GetTicks();

		SDL_RenderClear(this->_renderer);

		if (this->_loopPaused == false) {
			this->handleInputs();
			
			if (this->_currentWorld != NULL) {
                this->updateItems();
				this->render();
			}
		}

		SDL_RenderPresent(this->_renderer);

		endTicks = SDL_GetTicks();
		tickDelta = endTicks - startTicks;
        
		if (tickDelta < this->_frameLength) {
			SDL_Delay(this->_frameLength - tickDelta);
		}
	}
    
    // TODO: Frameskip
}

//WIP
void Engine::handleInputs() {
	SDL_Event inputEvent;
	while(SDL_PollEvent(&inputEvent)) {
            
		switch (inputEvent.type) {
			case SDL_QUIT:
				this->_loopEnded = true;
				break;
			
			case SDL_KEYDOWN:
				// Add to _activeKeyboardPresses w/start time
                // Notify of keyDown
				break;

			case SDL_KEYUP:
                // Notify of keyUp
                // If key in _activeKeyboardPresses, remove, notify of keyPressed w/start-end time
				break;

			case SDL_MOUSEMOTION:
                // Notify of mouseMoved
				break;

			case SDL_MOUSEBUTTONDOWN:
                // Notify of mouseDown
                // Add to _activeMousePresses w/start time
				break;

			case SDL_MOUSEBUTTONUP:
                // Notify of mouseUp
                // If button in _activeMousePresses, remove, notify of mousePressed w/start-end time
				break;

			case SDL_MOUSEWHEEL:
                // Notify of scroll
				break;
		}
	}	
}

//WIP
void Engine::updateItems() {

}

//WIP
void Engine::render() {

}

//Done
void Engine::attachWorld(EngineWorld *world) {
	if (this->_currentWorld != NULL) {
		this->detachWorld();
	}

    this->_currentWorld = world;
	this->_currentWorld->attachedToEngineWithRenderer(this->_renderer);
}

//Done
void Engine::detachWorld() {
	this->_currentWorld->detachedFromEngine();
	this->_currentWorld = NULL;
}

/* Teardown */

//WIP
void Engine::cleanUp() {
	if (this->_renderer != NULL) {
		SDL_DestroyRenderer(this->_renderer);
	}

	if (this->_window != NULL) {
		SDL_DestroyWindow(this->_window);
	}
    
    //TODO: Clean up mouse/keyboard presses

	IMG_Quit();
	SDL_Quit();
}

//Done
Engine::~Engine() {
	this->cleanUp();
}
