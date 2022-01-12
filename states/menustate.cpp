//
//  menustate.cpp
//  DroneWarsV3
//
//  Created by Jovian on 2021/12/13.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "menustate.hpp"

MenuState MenuState::m_MenuState;

void MenuState::init(SDL_Renderer* renderer,int wW, int wH)
{
    menuRenderer = renderer;
    splashScreen.setImage("splash1024.png", menuRenderer);
    if(splashScreen.getTexture()==NULL)
    {
        std::cout<<"Unable to load texture in menustate init"<<std::endl;
    }
    splashScreen.setSource(0, 0, 1920,1080 );
    int windowWidth = wW;
    int windowHeight = wH;
    splashScreen.setDestination(0, 0, windowWidth, windowHeight);

    menuGUI.initMenuGUI(menuRenderer, windowWidth, windowHeight,0);
    printf("MenuState Init Successful\n");
    mousePointer.w = 10;
    mousePointer.h = 10;
  
  //  initAudio();
    
}


void MenuState::pause()
{
    printf("MenuState Paused\n");
}

void MenuState::resume()
{
    printf("MenuState Resumed\n");
}
Player* MenuState::createNewPlayer()
{
    ////////////  new player stufff //////////
    
    ////  instatiate everything as the defaults ////
    player = new Player();

    player->setCurrentLevel(1);
    player->setHps(100);
    player->setMaxHps(100);
    player->setEnergy(100);
    player->setMaxEnergy(100);
    player->setShield(100);
    player->setMaxShield(100);
    player->setRareElements(0);
    player->setPreciousMetals(0);
    player->setScore(0);
    player->setDestination(200, 700, 200, 200);
    player->setCurrentWeapon(2);   ///weapon set to spread blaster
    ///////// end new player stuff ///////
    return player;
}

void MenuState::handleEvents(Game* game) //put our exit function back in business
// we can now quit with cross in corner.
{
    SDL_Event event;
    
    if (SDL_WaitEvent(&event)) {
        switch (event.type)
        {
            case SDL_QUIT:
                game->quit();
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
            {
              
                case SDLK_q:
                    game->quit();
                    break;
                    
            }
        }
    }
}

void MenuState::update(Game* game)
{
    menuGUI.update();
    if(menuGUI.getSelection()==0)
    {
        
        std::cout<<"New Game Selected"<<std::endl;
        game->changeState(BriefState::instance());
        player = createNewPlayer();
        /// OverWrite old game ///
    
        Savegame sg(player);
        BriefState::instance()->loadMissionBriefing(player);
    }
    if(menuGUI.getSelection()==1)
    {
        /// change to dockstate
        ///
        game->changeState(DockState::instance());
        /// dockstate will load the savegame.txt file and hence the player no need to initialize here
        std::cout<<"Load Game Selected"<<std::endl;
        
    }
    if(menuGUI.getSelection()==2)
    {
        game->quit();
        std::cout<<"Quit Game Selected"<<std::endl;
    }
}
void MenuState::draw(Object &object,int rotationAngle)
{
    SDL_Rect destination = object.getDestination();
    SDL_Rect source = object.getSource();
    SDL_RenderCopyEx(menuRenderer,object.getTexture(),&source,&destination,rotationAngle,NULL,SDL_FLIP_NONE);
}


void MenuState::render(Game* game)
{
    
    SDL_RenderClear(menuRenderer);
    draw(splashScreen,0);
    draw(menuGUI,0);
    menuGUI.drawButtons();
 
    
    SDL_RenderPresent(menuRenderer);
}
void MenuState::clean()
{
    printf("MenuState Clean Successfully\n");
    SDL_DestroyTexture(splashScreen.getTexture());
    menuGUI.setSelection(-1);
    menuGUI.clean();
}
