//
//  GameEngine.hpp
//  lib-eolipile
//
//  Created by Gabriel Banfalvi on 09/02/16.
//  Copyright © 2016 clueless. All rights reserved.
//

#ifndef GameEngine_hpp
#define GameEngine_hpp

#include <iostream>
#include <string>
#include <vector>

#include "SDLLibs.hpp"
#include "EngineInputHandler.hpp"

/**
 Games are comprised of a single Engine. The engine handles:
 
 - The game window and renderer.
 - The game loop (taking input and forwarding it, rendering the frame, handling framerates).
 - Attaching a world with items, which it'll ask to render when the time comes.
 
 Docs:
 https://wiki.libsdl.org/SDL_RenderPresent
 
 */

class EngineInputListener;
class EngineWorld;

class GameEngine {
    
private:
    std::string  *_windowName;
    SDL_Window   *_window;
    SDL_Renderer *_renderer;
    
    EngineWorld         *_currentWorld;
    EngineInputHandler  *_inputHandler;
    
    SDL_Event _searchedEvent;
    
    int _windowWidth;
    int _windowHeight;
    
    int _frameLength;
    
    bool _loopEnded;
    bool _loopPaused;
    
    /* Private lifecycle */
    
    void gameLoop(); // WIP
    void updateItems(); // WIP
    void render(); // WIP
    
    
public:
    GameEngine(int w, int h, int fps, std::string *name) :
        _windowWidth(w),
        _windowHeight(h),
        _frameLength(1000/fps),
        _windowName(name){
            _inputHandler = new EngineInputHandler(this);
        }; //Done
    
    /* Public lifecycle */
    
    bool loadWindow(); // Done
    
    void startLoop(); // Done
    bool pauseLoop(); // Done
    void endLoop(); // Done
    
    /* World attach/detach */
    
    void attachWorld(EngineWorld *world); // Done
    void detachWorld(); // Done
    
    /* Stuff you shouldn't use */
    
    SDL_Renderer* getRenderer();
    
    /* Teardown */
    
    void cleanUp(); // WIP
    
    ~GameEngine(); // Done
};

#endif /* GameEngine_hpp */
