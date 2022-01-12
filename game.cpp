//
//  game.cpp
//  sdlproject
//
//  Created by mac on 2021/12/31.
//

#include "game.hpp"

#include "gamestate.hpp"

Game::Game()  // Todo : move init into game constructor
{
    
}
void Game::init(const char* title, int width, int height,bool fullscreen)
{
    // initialize SDL
 //   SDL_PLATFORM_SUPPORTS_METAL;
//    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "metal");
    // I removed metal support not currently rendering on MAC OSX
  //  SDL_Init(SDL_INIT_EVERYTHING);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
 //   auto Width = DM.w;
 //   auto Height = DM.h;
    Width = DM.w;
    Height = DM.h;
    std::cout<<"Width: "<<Width<<std::endl; //768
    std::cout<<"Height: "<<Height<<std::endl; //1024
    m_bFullscreen = fullscreen;
    if(m_bFullscreen == true)
    {
      
        window = SDL_CreateWindow(title, 0 , 0 , Width, Height, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL  );
        
    }
    else
    {
        window = SDL_CreateWindow(title, 0 , 0 , Width, Height ,0);
        
    }
    
    renderer = SDL_CreateRenderer(window, -1,  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
 //   SDL_RenderGetMetalLayer(renderer);
    SDL_GL_SetSwapInterval(-1);
    
    m_bRunning = true;
    m_Paused = false;
    printf("Game Initialized Successfully\n");
}

/*
 cleans previous state if not empty, then pushes new state onto stack
 */
void Game::changeState(GameState* state)
{
    // cleanup the current state
    if ( !states.empty() ) {
        states.back()->clean();
        states.pop_back();
    }
    
    // store and init the new state
    states.push_back(state);
    states.back()->init(renderer,Width,Height);
}

/*

 Pushstate will push the next state on top of the stack instead of change state which pops the previous
 state off the stack. this one can be used for a pause or an overlapping screen where you want to preseve data from previous stack
 */
void Game::pushState(GameState* state)
{
    // pause current state
    if ( !states.empty() ) {
        states.back()->pause();
    }
    
    // store and init the new state
    states.push_back(state);
    states.back()->init(renderer,Width,Height);
}

/*
 Remove and resume previous state.
 */
void Game::popState()
{
    // cleanup the current state
    if ( !states.empty() )
    {
        states.back()->clean();
        states.pop_back();
    }
    
    // resume previous state
    if ( !states.empty() )
    {
        
        states.back()->resume();
    }
}


void Game::handleEvents()
{
    // let the state handle events
    states.back()->handleEvents(this);
}


void Game::update()
{
    // let the state update the game
    states.back()->update(this);
}

void Game::render()
{
    
    
    states.back()->render(this);
    
}
void Game::setPaused(bool b)
{
    m_Paused = b;
}
bool Game::isPaused()
{
    return m_Paused;
}
void Game::clean()
{
    while ( !states.empty() )
    {
        states.back()->clean();
        states.pop_back();
    }
    
    // shutdown SDL
    std::cout<<"Shutting down SDL " <<std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
   // SDL_VideoQuit();
    SDL_Quit();
}
