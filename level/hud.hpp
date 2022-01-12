//
//  hud.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/15.
//  Copyright © 2021 Jovian. All rights reserved.
//
#ifndef hud_hpp
#define hud_hpp

#include <stdio.h>
#include <iostream>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "gui.hpp"

//// Hud should be just for info and is non interactive, extends GUI class which adds text
/// 
class Hud : public GUI
{
public:
    Hud()
    :x(0),y(0),width(500),height(175)
    {
      
    }
    void initHud(SDL_Renderer* renderer,int &windowWidth,int &windowHeight);
   
    void clean();
private:
  
    int x,y,width,height;
    int windowWidth,windowHeight;
};
#endif /* hud_hpp */
