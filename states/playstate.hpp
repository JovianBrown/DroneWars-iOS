//
//  playstate.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/14.
//  Copyright © 2021 Jovian. All rights reserved.
//

#ifndef playstate_hpp
#define playstate_hpp

#include <stdio.h>
#include "SDL.h"
#include <iostream>
#include <fstream>
#include <string>
#include "game.hpp"
#include "gamestate.hpp"
#include "background.hpp"
#include "player.hpp"
#include "hud.hpp"
#include "item.hpp"
#include "projectile.hpp"
#include "timer.hpp"
#include "dockstate.hpp"
#include "savegame.hpp"
#include "audio.hpp"
#include "virtualjoystick.hpp"
#include "common.hpp"
#include "enemydrone.hpp"
#include "enemyprojectile.hpp"
class PlayState : public GameState
{
public:
    void init(SDL_Renderer* renderer,int wW, int wH);
    void clean();
    void pause();
    void resume();
    void handleEvents(Game* game);
    void update(Game* game);
    void render(Game* game);
    void checkBorders(Entity &object);
    void draw(Object &object,int rotationAngle);
    void drawBackground(Background &background);
    void loadPlayer(Player* p);
    void playerFire(); //made this public for now so it can be reached by the virtualjoystick class
    void shouldUpdateHUD(bool b);
    void enemyFire();
    
    static PlayState* instance()
    {
        return &m_PlayState;
    }
    
protected:
    PlayState()
    {
    }
    
private:
    static PlayState m_PlayState;
    

    SDL_Renderer* playRenderer;

    ///////// Player stuff //////////
 
    Player* player;    //player should be a pointer
    int defaultAcc; //declared for later use in movement vector
  //  player animations below
    int playerIdle;
    int playerReady;  //player getting ready
    int playerReadyReversed;
    int playerShield;
    //----------------------
    Projectile playersBullet;
    std::vector <Projectile> playersBullets;
    //// We don't want to continually convert ints to floats and whatnot for the HUD
    /// so we will define them here and update when they change
    float hullIntegrity;
    const char *hullIntegrityString=nullptr;
    std::string hI;
    const char *rareElementsString;
    const char *preciousMetalsString;
    const char *shieldString;
    const char *levelString;
    const char *scoreString;
    //////////////// End player stuff///////////
    EnemyDrone enemyDrone;
    EnemyProjectile enemysBullet;
    std::vector <EnemyProjectile> enemysBullets;
    std::vector <Entity> asteroids;
    Timer enemyFireTimer; //determine how fast the enemy drone can fire
    
    Entity asteroid;

    ///Asteroid animations below///
    int asteroidIdle;
    int asteroidExplode;
    //////////////
    
    ///////Level and BG stuff//////
    Hud hud;
    bool updateHUD;
    int* levelH=nullptr;
    int levelHeight;
    int windowWidth,windowHeight;
    int currentLevel; //using temporarily to calculate asteroid speed rand(1,currentLevel)+5
    std::vector<Background> backgrounds;
    Object shieldAlert;
    Object hullAlert;
    Uint16 lastFrame;
    Uint16 frameCount;
    Timer asteroidTimer;
    Timer* levelTimer=nullptr;
    
    bool shouldDiplayHullAlert;
    bool shouldDiplayShieldAlert;
    std::vector<std::string> levelInfo;
    std::vector<std::string> texturePaths;

    VirtualJoystick* virtualJoystick;
    /////////////end Level BG stuff///////
    ////// Items /////
    Item rareElement;
    Item energyPulse;
    Item preciousMetal;

    std::vector<Item> items;
   
    ///// Items End //////
    void spawnItem(int x, int y);
    void spawnAsteroid();
    void spawnFragment(Entity asteroid);
    void spawnEnemy();
    bool checkCollision(SDL_Rect A, SDL_Rect B);
    void loadLevel(int levelNumber);
    void updatePlayerStats();
};

#endif /* playstate_hpp */
