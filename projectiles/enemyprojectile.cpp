//
//  enemyprojectile.cpp
//  dronewars
//
//  Created by mac on 2022/1/11.
//

#include "enemyprojectile.hpp"
enum ENEMY_PROJECTILE_TYPES
{
    SMALL_ENEMY_BLASTER, BOLT_ENEMY_BLASTER
};
void EnemyProjectile::init(int type,SDL_Renderer* renderer)
{
    this->projectileType = type;
    if(type == SMALL_ENEMY_BLASTER)
    {
        setImage("bluebullet.png", renderer);
        setSource(0, 0, 100, 100);
        setDestination(0, 0, 20, 20);
        this->speed = 18;
        this->type = SMALL_ENEMY_BLASTER;
        this->damage = 20;
        this->name = "Small Blaster";
        this->projectileBehavior = 0;
        
    }
    if(type == BOLT_ENEMY_BLASTER)
    {
        setImage("enemyblasterbolt.png", renderer);
        setSource(0, 0, 100, 100);
        setDestination(0, 0, 50, 50);
        this->speed = 14;
        this->type = BOLT_ENEMY_BLASTER;
        this->damage = 30;
        this->name = "Wide Blue Blaster";
        this->projectileBehavior = 0;
        
    }
}

void EnemyProjectile::update()
{
    
    if(projectileBehavior==0)
    {
        setDestination(getDestination().x, getDestination().y+speed, getDestination().w, getDestination().h);
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
