//
//  main.cpp
//  Dronewars
//
//  Created by mac on 2021/12/4.
//  Copyright © 2021 Jovian. All rights reserved.
//


#include <iostream>
#include "game.hpp"
#include "SDL_main.h"
#include "menustate.hpp"
#include "pausestate.hpp"
#include "audio.hpp"
using namespace std;
Game game;

int HandleAppEvents(void *userdata, SDL_Event *event)
{
    switch (event->type)
    {
        case SDL_APP_TERMINATING:
            std::cout<<"Called Terminate App"<<std::endl;
            
            /* Terminate the app.
             Shut everything down before returning from this function.
             */
            return 0;
        case SDL_APP_LOWMEMORY:
            /* You will get this when your app is paused and iOS wants more memory.
             Release as much memory as possible.
             */
            return 0;
        case SDL_APP_WILLENTERBACKGROUND:
            /* Prepare your app to go into the background.  Stop loops, etc.
             This gets called when the user hits the home button, or gets a call.
             */
            return 0;
        case SDL_APP_DIDENTERBACKGROUND:
            /* This will get called if the user accepted whatever sent your app to the background.
             If the user got a phone call and canceled it, you'll instead get an SDL_APP_DIDENTERFOREGROUND event and restart your loops.
             When you get this, you have 5 seconds to save all your state or the app will be terminated.
             Your app is NOT active at this point.
             */
           // game.pushState(PauseState);
            game.setPaused(true);
          //  game.pushState(PauseState::instance());
            std::cout<<"Did enter background"<<std::endl;
            return 0;
        case SDL_APP_WILLENTERFOREGROUND:
            /* This call happens when your app is coming back to the foreground.
             Restore all your state here.
             */
            return 0;
        case SDL_APP_DIDENTERFOREGROUND:
            /* Restart your loops here.
             Your app is interactive and getting CPU again.
             */
           // game.popState();
            game.setPaused(false);

            return 0;
        default:
            /* No special processing, add it to the event queue */
            return 1;
    }
}

int main(int argc,char *argv[])
{
    SDL_SetEventFilter(HandleAppEvents, NULL); // this is for handling IOS app events

 //   const int windowWidth = 768;
 //   const int windowHeight = 1024;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    auto windowWidth = DM.w;
    auto windowHeight = DM.h;
    std::cout<<"called main function "<<std::endl;
    std::cout<<"window width: "<<DM.w<<std::endl;
    std::cout<<"window height: "<<DM.h<<std::endl;

    const int FPS =60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
    
    game.init("DroneWars v0.3", windowWidth, windowHeight, true);
    initAudio();
    game.changeState(MenuState::instance());
    
    
    while(game.running())
    {
        frameStart = SDL_GetTicks();
        
        game.handleEvents();
        game.update();
        game.render();
        
        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay-frameTime);
        }
    }
    
    // cleanup the engine
    game.clean();
    endAudio();
    std::cout<<"Called game clean"<<std::endl;
    
    return 0;
}
