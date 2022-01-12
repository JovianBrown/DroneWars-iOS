//
//  menustate.hpp
//  DroneWarsV3
//
//  Created by Jovian on 2021/12/13.
//  Copyright © 2021 Jovian. All rights reserved.
//

#ifndef menustate_hpp
#define menustate_hpp

#include <stdio.h>
#include "gamestate.hpp"
#include "SDL.h"
#include "game.hpp"
#include "menugui.hpp"
#include "player.hpp"
#include "briefstate.hpp"
#include "savegame.hpp"
#include "loadgame.hpp"
#include "dockstate.hpp"

class MenuState : public GameState
{
public:
    void init(SDL_Renderer* renderer,int windowWidth, int windowHeight);
    
    void clean();
    
    void pause();
    void resume();
    
    void handleEvents(Game* game);
    void update(Game* game);
    void draw(Object &object,int rotationAngle);
    void render(Game* game);
    
    // Implement Singleton Pattern
    static MenuState* instance()
    {
        return &m_MenuState;
    }
    
protected:
    
    MenuState() {}
    
private:
    static MenuState m_MenuState;
    Object splashScreen;
    SDL_Renderer* menuRenderer;
    MenuGUI menuGUI;
    Player* player; //for a new player object which will be used in the next state
    Player* createNewPlayer();
    SDL_Rect mousePointer;
    bool checkCollision(SDL_Rect rectA, SDL_Rect rectB);
};

#endif /* menustate_hpp */
