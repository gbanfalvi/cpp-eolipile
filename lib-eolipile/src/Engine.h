
#ifndef _INCL_ENGINE_H
#define _INCL_ENGINE_H

#ifdef MACOSX
	#import <SDL2/SDL.h>
	#import <SDL2_image/SDL_image.h>
#endif

#include <iostream>
#include <string>
#include <vector>

#include "EngineWorld.h"

/**
 Games are comprised of a single Engine. The engine handles:
 
 - The game window and renderer.
 - The game loop (taking input and forwarding it, rendering the frame, handling framerates).
 - Attaching a world with items, which it'll ask to render when the time comes.
 
 Docs:
 https://wiki.libsdl.org/SDL_RenderPresent
 
*/

class Engine {
    
private:
    std::string  *_windowName;
    SDL_Window   *_window;
	SDL_Renderer *_renderer;
	
	EngineWorld *_currentWorld;

	std::vector<SDL_KeyboardEvent>    _activeKeyboardPresses;
	std::vector<SDL_MouseButtonEvent> _activeMousePresses;

	int _windowWidth;
	int _windowHeight;
	
	int _frameLength;

	bool _loopEnded;
	bool _loopPaused;

	void notifyOfKeyboardPress();
	void notifyOfMousePress();

	void gameLoop();
	void updateItems();
	void handleInputs();
	void render();

public:

	// Create an engine with a specific screen size, framerate and window title.
	Engine(int w, int h, int fps, std::string *name);

	// Creates the window and sets up renderer and image-loading lib.
    bool loadWindow();

	// Starts the game loop. Call only once.
	void startLoop();

	// Pause the game loop. Not useful right now. Returns true if paused and false if unpaused.
	bool pauseLoop();

	// Ends the loop. After this you can call cleanUp().
	void endLoop();

    // Attaches the world (and its items to the engine). Generates textures for all the items.
	void attachWorld(EngineWorld *world);
    
    // Detaches the world. Cleans up all the textures.
	void detachWorld();
	
	// Gets rid of the window and the renderer as well as cleaning up SDL and SDLImage resources.
	// If the engine is deleted, it'll call cleanUp(), so it might not be necessary to call this
	// explicitly.
	void cleanUp();

	~Engine();
};

#endif
