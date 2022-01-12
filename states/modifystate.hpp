//
//  modifystate.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/18.
//  Copyright © 2021 Jovian. All rights reserved.
//

#ifndef modifystate_hpp
#define modifystate_hpp

#include <stdio.h>
#include "gamestate.hpp"
#include "hud.hpp"
#include "menugui.hpp"
#include "player.hpp"
#include "projectile.hpp"
#include "item.hpp"
#include "barteritem.hpp"
#include "common.hpp"

class ModifyState : public GameState
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
    static ModifyState* instance()
    {
        return &m_ModifyState;
    }
    
protected:
    
    ModifyState() {}
    
private:
    void initPlayer();
    void drawSellSpace();
    void drawBuySpace();

    static ModifyState m_ModifyState;
    Hud hud;
    MenuGUI modifyGUI;

    SDL_Renderer* modifyRenderer;
    SDL_Rect barterSpace;
    Player* player;

    const char * playersCurrentLevel;
    const char * playerHps;
    const char * maxHps;
    const char * rareElements;
    const char * preciousMetals;
    unsigned int u_playerHps;
    unsigned int u_playerMaxHps;
    float hullIntegrity;
    int playersScore;
    int playersCredits;
    int currentWeapon;
    Projectile playersWeapon;
    std::vector <std::string> playerStats;
    ////// Player Items  /////
    Item rareElement;
    Item preciousMetal;
    Item energyPulse;
////////////////// Barter Items ////////
    BarterItem blasterBlue;
    BarterItem blasterWideGreen;
    std::vector<BarterItem> barterItems;
    
    /////////////////////
    Object selectionBox;  /// to show which item is selected currentlyt
    SDL_Rect mousePointer;

    std::vector<Item> items;
    
    
    ///// Items End //////
    
    
};

#endif /* modifystate_hpp */
