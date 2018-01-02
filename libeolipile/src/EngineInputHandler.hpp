/**
 * Just polls basic input in the engine loop, nothing more, really. It was part of the engine but I
 * moved it out when I realized that the code could be encapsulated
 */

#ifndef EngineInputHandler_hpp
#define EngineInputHandler_hpp

#include <stdio.h>
#include <vector>

#include "SDLLibs.hpp"
#include "EngineInputListener.hpp"

class GameEngine;

MouseInput buttonToMouseInput(Uint32 button);
bool buttonInMask(MouseInput button, MouseInput mask);

class EngineInputHandler {
    
private:
    EngineInputListener *_currentInputListener;
    GameEngine *_engine;
    
    std::vector<SDL_Event> _activeKeyboardPresses;
    std::vector<SDL_Event> _activeMousePresses;
    
    bool _searchSDLEventsFor(SDL_Event event);
    SDL_Event _searchedEvent;
    
public:
    
    EngineInputHandler(GameEngine *engine);
    
    inline void setListener(EngineInputListener *listener) {
        _currentInputListener = listener;
    }
    
    inline void clearListener() {
        _currentInputListener = NULL;
    }
    
    void handleInputs();
    
};

#endif /* EngineInputHandler_hpp */
