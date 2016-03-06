//
//  EngineDimensions.cpp
//  lib-eolipile
//
//  Created by Gabriel Banfalvi on 27/02/16.
//  Copyright © 2016 clueless. All rights reserved.
//

#include "EngineInputListener.hpp"

inline MouseInput buttonToMouseInput(Uint32 button) {
    return SDL_BUTTON(button);
}

inline bool buttonInMask(MouseInput button, MouseInput mask) {
    return button & mask;
}

void EngineInputListener::keyDown(SDL_Scancode physical, SDL_Keycode mapped, Uint16 modifier, Uint32 timestamp) {
    #ifdef DEBUG
        std::cout << "Key down physical " << SDL_GetScancodeName(physical) << " mapped to " << SDL_GetKeyName(mapped) << std::endl;
    #endif
}

void EngineInputListener::keyUp(SDL_Scancode physical, SDL_Keycode mapped, Uint16 modifier, Uint32 timestamp) {
    #ifdef DEBUG
        std::cout << "Key up physical " << SDL_GetScancodeName(physical) << " mapped to " << SDL_GetKeyName(mapped) << std::endl;
    #endif
}

void EngineInputListener::keyPressed(SDL_Scancode physical,
                                     SDL_Keycode mapped,
                                     Uint16 modifier,
                                     Uint32 timestampStart,
                                     Uint32 timestampDuration) {
    #ifdef DEBUG
        std::cout << "Key pressed physical " << SDL_GetScancodeName(physical) << " mapped to " << SDL_GetKeyName(mapped) << std::endl;
    #endif
}

void EngineInputListener::mouseMoved(Sint32 x, Sint32 y, MouseInput buttonMask, Uint32 timestamp) {
    #ifdef DEBUG
        std::cout << "Mouse moved to " << x << ", " << y << std::endl;
    #endif
}

void EngineInputListener::mouseButtonDown(Sint32 x, Sint32 y, MouseInput buttonMask, Uint32 timestamp) {
    #ifdef DEBUG
        std::cout << "Mouse pressed at " << x << ", " << y << std::endl;
    #endif
}

void EngineInputListener::mouseButtonUp(Sint32 x, Sint32 y, MouseInput buttonMask, Uint32 timestamp) {
    #ifdef DEBUG
        std::cout << "Mouse raised at " << x << ", " << y << std::endl;
    #endif
}

void EngineInputListener::mouseClicked(Sint32 x, Sint32 y, MouseInput buttonMask, Uint32 timestamp, Uint32 timestampDuration) {
    #ifdef DEBUG
        std::cout << "Mouse clicked at " << x << ", " << y << std::endl;
    #endif
}

void EngineInputListener::mouseScrolled(Sint32 x, Sint32 y, bool flipped, Uint32 timestamp) {
    #ifdef DEBUG
        std::cout << "Mouse scrolled at " << x << ", " << y << std::endl;
    #endif
}
