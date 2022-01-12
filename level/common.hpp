//
//  common.hpp
//  dronewars
//
//  Created by mac on 2022/1/1.
//
#ifndef common_hpp
#define common_hpp

#include <stdio.h>
#include "SDL.h"
extern int randomInt(int min, int max);
extern float randomFloat(float min, float max);
extern void fatalError(const char *string);
extern double updateDeltaTime(void);
extern bool checkCollision(SDL_Rect rectA, SDL_Rect rectB);

#endif /* common_hpp */
