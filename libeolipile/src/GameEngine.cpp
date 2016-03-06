//
//  GameEngine.cpp
//  lib-eolipile
//
//  Created by Gabriel Banfalvi on 09/02/16.
//  Copyright © 2016 clueless. All rights reserved.
//

#include "GameEngine.hpp"
#include "EngineWorld.hpp"
#include "EngineInputListener.hpp"
#include "EngineInputHandler.hpp"

/* Private lifecycle */

void GameEngine::gameLoop() {
    
    Uint32 startTicks, endTicks, tickDelta;
    bool lagging = false;
    
    while (_loopEnded == false) {
        startTicks = SDL_GetTicks();
        
        SDL_RenderClear(_renderer);
        
        if (_loopPaused == false) {
            //_inputHandler->handleInputs();
            
            if (_currentWorld != NULL) {
                updateItems();
                
                if (!lagging) {
                    render();
                }
            }
        }
        
        SDL_RenderPresent(_renderer);
        
        endTicks = SDL_GetTicks();
        tickDelta = endTicks - startTicks;
        
        if (tickDelta < _frameLength) {
            SDL_Delay(_frameLength - tickDelta);
        }
        
        lagging = tickDelta > _frameLength;
    }
}

void GameEngine::updateItems() { }



void GameEngine::render() { }

/* Public lifecycle */

bool GameEngine::loadWindow() {
    
    // Load SDL support
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    // Load SDL_image support
    int supportedImageFormats = IMG_INIT_JPG|IMG_INIT_PNG; //SDL supports bmp already
    
    int loadedImageSupport = IMG_Init(supportedImageFormats);
    if ((loadedImageSupport & supportedImageFormats) != supportedImageFormats) {
        std::cout << "IMG_Init Error: " << IMG_GetError() << std::endl;
        return false;
    }
    
    // Create a window
    _window = SDL_CreateWindow(_windowName->c_str(),
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               _windowWidth,
                               _windowHeight,
                               SDL_WINDOW_SHOWN);
    if (_window == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        cleanUp();
        return false;
    }
    
    // Create a renderer
    _renderer = SDL_CreateRenderer(_window,
                                   -1,
                                   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_renderer == nullptr){
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        cleanUp();
        return false;
    }
    
    return true;
}

void GameEngine::startLoop() {
    _loopEnded = false;
    _loopPaused = false;
    
    gameLoop();
}

bool GameEngine::pauseLoop() {
    _loopPaused = !_loopPaused;
    return _loopPaused;
}

void GameEngine::endLoop() {
    _loopEnded = true;
}

/* World attach/detach */

void GameEngine::attachWorld(EngineWorld *world) {
    if (_currentWorld != NULL) {
        detachWorld();
    }
    
    _currentWorld = world;
    _currentWorld->attachedToEngineWithRenderer(_renderer);
}

void GameEngine::detachWorld() {
    _currentWorld->detachedFromEngine();
    _currentWorld = NULL;
}

/* Stuff you shouldn't use */

SDL_Renderer* GameEngine::getRenderer() {
    return _renderer;
}

/* Teardown */

void GameEngine::cleanUp() {
    if (_renderer != NULL) {
        SDL_DestroyRenderer(_renderer);
    }
    
    if (_window != NULL) {
        SDL_DestroyWindow(_window);
    }
    
    delete _inputHandler;
    
    IMG_Quit();
    SDL_Quit();
}

GameEngine::~GameEngine() {
    cleanUp();
}