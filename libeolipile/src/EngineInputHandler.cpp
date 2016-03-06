//
//  EngineInputHandler.cpp
//  lib-eolipile
//
//  Created by Gabriel Banfalvi on 28/02/16.
//  Copyright © 2016 clueless. All rights reserved.
//

#include "EngineInputHandler.hpp"
#include "GameEngine.hpp"

EngineInputHandler::EngineInputHandler(GameEngine *engine):
    _activeKeyboardPresses(),
    _activeMousePresses() {
        _engine = engine;
}

inline bool EngineInputHandler::_searchSDLEventsFor(SDL_Event event) {
    if (_searchedEvent.type == SDL_KEYDOWN || _searchedEvent.type == SDL_KEYUP) {
        return event.key.keysym.scancode == _searchedEvent.key.keysym.scancode;
    }
    return false;
}

inline void EngineInputHandler::handleInputs() {
    SDL_Event inputEvent;
    while(SDL_PollEvent(&inputEvent)) {
        
        if (_currentInputListener == NULL) {
            return;
        }
        
        switch (inputEvent.type) {
            case SDL_QUIT:
                _engine->endLoop();
                break;
                
            case SDL_KEYDOWN: {
                _activeKeyboardPresses.push_back(inputEvent);
                _currentInputListener->keyDown(inputEvent.key.keysym.scancode,
                                               inputEvent.key.keysym.sym,
                                               inputEvent.key.keysym.mod,
                                               inputEvent.key.timestamp);
                break;
                
            } case SDL_KEYUP: {
                _currentInputListener->keyUp(inputEvent.key.keysym.scancode,
                                             inputEvent.key.keysym.sym,
                                             inputEvent.key.keysym.mod,
                                             inputEvent.key.timestamp);
                
                _searchedEvent = inputEvent;
                
                std::vector<SDL_Event>::iterator event = std::find_if(_activeKeyboardPresses.begin(),
                                                                      _activeKeyboardPresses.end(),
                                                                      std::bind(&EngineInputHandler::_searchSDLEventsFor, this, std::placeholders::_1));
                
                if (event != _activeKeyboardPresses.end()) {
                    SDL_Event origEvent = *event;
                    _currentInputListener->keyPressed(inputEvent.key.keysym.scancode,
                                                      inputEvent.key.keysym.sym,
                                                      inputEvent.key.keysym.mod,
                                                      origEvent.key.timestamp,
                                                      inputEvent.key.timestamp - origEvent.key.timestamp);
                    
                    _activeKeyboardPresses.erase(event);
                }
                
                break;
                
            } case SDL_MOUSEMOTION: {
                _currentInputListener->mouseMoved(inputEvent.motion.x,
                                                  inputEvent.motion.y,
                                                  inputEvent.motion.state,
                                                  inputEvent.motion.timestamp);
                break;
                
            } case SDL_MOUSEBUTTONDOWN: {
                _activeMousePresses.push_back(inputEvent);
                _currentInputListener->mouseButtonDown(inputEvent.button.x,
                                                       inputEvent.button.y,
                                                       buttonToMouseInput(inputEvent.button.button),
                                                       inputEvent.button.timestamp);
                break;
                
            } case SDL_MOUSEBUTTONUP: {
                _currentInputListener->mouseButtonUp(inputEvent.button.x,
                                                     inputEvent.button.y,
                                                     buttonToMouseInput(inputEvent.button.button),
                                                     inputEvent.button.timestamp);
                _searchedEvent = inputEvent;
                
                std::vector<SDL_Event>::iterator event = std::find_if(_activeMousePresses.begin(),
                                                                      _activeMousePresses.end(),
                                                                      std::bind(&EngineInputHandler::_searchSDLEventsFor, this, std::placeholders::_1));
                
                if (event != _activeMousePresses.end()) {
                    SDL_Event origEvent = *event;
                    _currentInputListener->mouseClicked(inputEvent.button.x,
                                                        inputEvent.button.y,
                                                        buttonToMouseInput(inputEvent.button.button),
                                                        origEvent.button.timestamp,
                                                        inputEvent.button.timestamp - origEvent.button.timestamp);
                    
                    _activeMousePresses.erase(event);
                }
                
                break;
                
            } case SDL_MOUSEWHEEL: {
                _currentInputListener->mouseScrolled(inputEvent.wheel.x,
                                                     inputEvent.wheel.y,
                                                     inputEvent.wheel.direction == SDL_MOUSEWHEEL_NORMAL,
                                                     inputEvent.wheel.timestamp);
                break;
            }
        }
    }
}
