//
//  common.cpp
//  dronewars
//
//  Created by mac on 2022/1/1.
//


#include "common.hpp"
#include "SDL.h"
#include <stdlib.h>

/*
 Produces a random int x, min <= x <= max
 following a uniform distribution
 */
int
randomInt(int min, int max)
{
    return min + rand() % (max - min + 1);
}

/*
 Produces a random float x, min <= x <= max
 following a uniform distribution
 */
float
randomFloat(float min, float max)
{
    return rand() / (float) RAND_MAX *(max - min) + min;
}

void
fatalError(const char *string)
{
    printf("%s: %s\n", string, SDL_GetError());
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, string, SDL_GetError(), NULL);
    exit(1);
}

static Uint64 prevTime = 0;

double
updateDeltaTime(void)
{
    Uint64 curTime;
    double deltaTime;
    
    if (prevTime == 0) {
        prevTime = SDL_GetPerformanceCounter();
    }
    
    curTime = SDL_GetPerformanceCounter();
    deltaTime = (double) (curTime - prevTime) / (double) SDL_GetPerformanceFrequency();
    prevTime = curTime;
    
    return deltaTime;
}

bool checkCollision(SDL_Rect rectA, SDL_Rect rectB)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    //Calculate the sides of rect A
    leftA = rectA.x;
    rightA = rectA.x + rectA.w;
    topA = rectA.y;
    bottomA = rectA.y + rectA.h;
    
    //Calculate the sides of rect B
    leftB = rectB.x;
    rightB = rectB.x + rectB.w;
    topB = rectB.y;
    bottomB = rectB.y + rectB.h;
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}
