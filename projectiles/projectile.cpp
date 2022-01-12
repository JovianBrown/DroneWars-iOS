//
//  projectile.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/15.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "projectile.hpp"
enum PROJECTILE_TYPES
{
    SMALL_BLUE_BULLET,BLUE_LASER_WIDE,GREEN_SUPER_WIDE,SPREAD_BLASTER
};
void Projectile::init(int type,SDL_Renderer* renderer)
{
    this->projectileType = type;
    if(type == SMALL_BLUE_BULLET)
    {
        setImage("bluebullet.png", renderer);
        setSource(0, 0, 100, 100);
        setDestination(0, 0, 20, 20);
        this->speed = 18;
        this->type = SMALL_BLUE_BULLET;
        this->damage = 20;
        this->name = "Small Blaster";
        this->projectileBehavior = 0;

    }
    if(type == BLUE_LASER_WIDE)
    {
        setImage("bluelaserwide.png", renderer);
        setSource(0, 0, 100, 100);
        setDestination(0, 0, 25, 25);
        this->speed = 14;
        this->type = BLUE_LASER_WIDE;
        this->damage = 30;
        this->name = "Wide Blue Blaster";
        this->projectileBehavior = 0;


    }
    if(type == GREEN_SUPER_WIDE)
    {
        setImage("greenlaserwide.png", renderer);
        setSource(0, 0, 200, 100);
        setDestination(0, 0, 70, 35);
        this->speed = 16;
        this->type = GREEN_SUPER_WIDE;
        this->damage = 38;
        this->name = "Super Wide Blaster";
        this->projectileBehavior = 0;

        
    }
    if(type == SPREAD_BLASTER)
    {
        setImage("reddot.png", renderer);
        setSource(0, 0, 100, 100);
        setDestination(0, 0, 50, 50);
        this->speed = 13;
        this->type = SPREAD_BLASTER;
        this->damage = 20;
        this->name = "Spread Blaster";
        this->projectileBehavior = 1; //spread behavior
        
        
    }
}

void Projectile::update()
{
    
    if(projectileBehavior==0)
    {
        setDestination(getDestination().x, getDestination().y-speed, getDestination().w, getDestination().h);
    }
    if(projectileBehavior==1)
    {
        uint8_t xDirection = rand()%2+1;
        Sint8 xDirectionAmount = rand()%10;
        
        if(xDirection == 1)
        {
            setDestination(getDestination().x-xDirectionAmount, getDestination().y-speed, getDestination().w, getDestination().h);
        }
        if(xDirection == 2)
        {
            setDestination(getDestination().x+xDirectionAmount, getDestination().y-speed, getDestination().w, getDestination().h);
        }
        else
        {
            setDestination(getDestination().x, getDestination().y-speed, getDestination().w, getDestination().h);
        }
        
    }
    
}
