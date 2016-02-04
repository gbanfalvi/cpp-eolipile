

#ifndef _INCL_ENGINE_INPUT_H
#define _INCL_ENGINE_INPUT_H

#ifdef MACOSX
	#import <SDL2/SDL.h>
	#import <SDL2_image/SDL_image.h>
#endif

#import <iostream>

/**
	Override the methods you care about in this class and then set it as the input listener to the 
	engine to listen to the overrriden events.

	Keyboard events are surprisingly complicated, so I'm provideng with the scan code, the key code 
	and the modifier. Because depending on the circumstances you might need one or the other. I 
	quote below:

	"Which one to use is left to the application: scancodes are suited in situations where controls 
	are layout-dependent (eg. the "WASD" keys as left-handed arrow keys), whereas keycodes are 
	better suited to situations where controls are character-dependent (eg. the "I" key for 
	Inventory)."

	Source: https://wiki.libsdl.org/CategoryKeyboard

	Both types' constants to check for are listed here: https://wiki.libsdl.org/SDL_Keycode

	Finally, modifiers (shift, alt, win key) are listed here: https://wiki.libsdl.org/SDL_Keymod
*/

class EngineInputListener {

	/** When a key is first pressed down */
	void keyDown(SDL_Scancode physical, SDL_Keycode mapped, SDL_Keymod modifier, Uint32 timestamp) {
		#ifdef DEBUG
			std::cout << "Key down physical " << SDL_GetScancodeName(physical) <<
				" mapped to " << SDL_GetKeyName(mapped) << std::endl;
		#endif
	}

	/** When a key is released */
	void keyUp(SDL_Scancode physical, SDL_Keycode mapped, SDL_Keymod modifier, Uint32 timestamp) {
		#ifdef DEBUG
			std::cout << "Key up physical " << SDL_GetScancodeName(physical) <<
				" mapped to " << SDL_GetKeyName(mapped) << std::endl;
		#endif
	}

	/** When a key is pressed, then released */
	void keyPressed(SDL_Scancode physical, SDL_Keycode mapped, SDL_Keymod modifier, 
		Uint32 timestampStart, Uint32 timestampDuration) {

		#ifdef DEBUG
			std::cout << "Key pressed physical " << SDL_GetScancodeName(physical) <<
				" mapped to " << SDL_GetKeyName(mapped) << std::endl;
		#endif
	}

	void mouseMoved() {

	}

	void mouseButtonDown() {

	}

	void mouseButtonUp() {

	}

	void mouseClicked() {

	}

	void mouseScroll() {

	}

};

#endif