

#ifndef _INCL_ENGINE_INPUT_H
#define _INCL_ENGINE_INPUT_H

#include <iostream>
#include "SDLLibs.hpp"

/**
	Override the methods you care about in this class and then set it as the input listener to the 
	engine to listen to the overrriden events.

	Keyboard events are surprisingly complicated, so I'm providing with the scan code, the key code
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

typedef Uint32 MouseInput;

const MouseInput MouseInputLeftButton   = SDL_BUTTON_LMASK;
const MouseInput MouseInputRightButton  = SDL_BUTTON_RMASK;
const MouseInput MouseInputMiddleButton = SDL_BUTTON_MMASK;
const MouseInput MouseInputX1Button     = SDL_BUTTON_X1MASK;
const MouseInput MouseInputX2Button     = SDL_BUTTON_X2MASK;

class EngineInputListener {

public:
    
    void keyDown(SDL_Scancode physical, SDL_Keycode mapped, Uint16 modifier, Uint32 timestamp);
    void keyUp(SDL_Scancode physical, SDL_Keycode mapped, Uint16 modifier, Uint32 timestamp);
    void keyPressed(SDL_Scancode physical, SDL_Keycode mapped, Uint16 modifier, Uint32 timestampStart, Uint32 timestampDuration);
    
    void mouseButtonDown(Sint32 x, Sint32 y, MouseInput buttonMask, Uint32 timestamp);
    void mouseButtonUp(Sint32 x, Sint32 y, MouseInput buttonMask, Uint32 timestamp);
    void mouseClicked(Sint32 x, Sint32 y, MouseInput buttonMask, Uint32 timestamp, Uint32 timestampDuration);
    void mouseMoved(Sint32 x, Sint32 y, MouseInput buttonMask, Uint32 timestamp);
    void mouseScrolled(Sint32 x, Sint32 y, bool flipped, Uint32 timestamp);
};

#endif