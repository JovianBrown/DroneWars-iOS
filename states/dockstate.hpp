//
//  dockstate.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/17.
//  Copyright © 2021 Jovian. All rights reserved.
//

#ifndef dockstate_hpp
#define dockstate_hpp

#include <stdio.h>
#include "gamestate.hpp"
#include "hud.hpp"
#include "menustate.hpp"
#include "playstate.hpp"
#include "modifystate.hpp"
#include <vector>
#include "background.hpp"
#include "menugui.hpp"
#include "common.hpp"

class DockState: public GameState
{
public:
    void init(SDL_Renderer* renderer,int windowWidth,int windowHeight);
    void initPlayer();
    void clean();
    
    void pause();
    void resume();
    
    void handleEvents(Game* game);
    void update(Game* game);
    void draw(Object &object,int rotationAngle);
    void drawBackground(Background &background);
    void render(Game* game);
    
    // Implement Singleton Pattern
    static DockState* instance()
    {
        return &m_dockState;
    }
    
protected:
    
    DockState() {}
    
private:
    static DockState m_dockState;
    Object dockScreen;
    SDL_Renderer* dockRenderer;
    Hud hud;
    MenuGUI dockMenu;
    Background background;
    std::vector <std::string> playerStats;
    
    int* levelH=nullptr;
    int levelHeight;
  ///// const chars are for the HUD /////
    const char * playersCurrentLevel;
    const char * playerHps;
    const char * maxHps;
    const char * rareElements;
    const char * preciousMetals;
    const char * playersWeapon;
///////////////////////////
    unsigned int u_playerHps;
    unsigned int u_playerMaxHps;
    unsigned int u_playersWeapon;
    float hullIntegrity;
    int playersScore;
    int playersCredits;
//    int playersWeapon;
    Player* player;
   

};


#endif /* dockstate_hpp */
