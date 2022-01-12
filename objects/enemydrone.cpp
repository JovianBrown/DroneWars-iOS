//
//  enemydrone.cpp
//  dronewars
//
//  Created by mac on 2022/1/11.
//

#include "enemydrone.hpp"

void EnemyDrone::init(int dT,SDL_Renderer* renderer)
{
    setActive(true);
    setShouldFire(false);
    offset = 35;
    if(dT == TRASH_DRONE)
    {
        setImage("trashdronesprite.png", renderer);
        setSource(0, 0, 200, 200);
        setDefaultAcc(2.0);
        setMaxAcc(10);
        setHps(200);
        setMass(60);
        setDestination(1, 1, 200, 200);
        trashDroneIdleAnim = this->createCycle(8, 4, 0, 0, 200, 200, 30, true, false, false);
        trashDroneExplodeAmin = this->createCycle(8, 3, 0, 3, 200, 200, 60, false, false, false);
        this->setCurrentAnimation(trashDroneIdleAnim);

    }
    if(dT == UFO_DRONE)
    {
        setImage("ufodronespritesheet.png", renderer);
        setSource(0, 0, 200, 200);
        setDefaultAcc(4.0);
        setMaxAcc(10);
        setHps(350);
        setMass(60);
        ufoDroneIdleAnim = this->createCycle(8, 3, 0, 0, 200, 200, 30, true, false, false);
        ufoDroneExplodeAmin = this->createCycle(8, 3, 0, 2, 200, 200, 30, false, false, false);
        this->setCurrentAnimation(ufoDroneIdleAnim);
        setDestination(300, 1, 150, 150);

    }
}

void EnemyDrone::update(int playerX,int playerY)
{
 //   std::cout<<"Player x : "<<playerX<<std::endl;
 //   std::cout<<"Player y : "<<playerY<<std::endl;

  //  if(getHps()<1)
  //  {
  //      this->setActive(false); //should change this to explosion animation
  //  }
    this->checkSpeed();
    
    this->setDestination(this->getDestination().x+this->getXAcc(), this->getDestination().y+this->getYAcc(),this->getDestination().w, this->getDestination().h);
    if(playerY>this->getDestination().y+offset) /// keep 20 pixels north of player
    {
        this->applyForce(this->getDefaultAcc(), SOUTH);
    }
    if(playerY<this->getDestination().y-offset) /// keep 20 pixels north of player
    {

        this->applyForce(this->getDefaultAcc(), NORTH);
    }
    if(playerX>this->getDestination().x)
    {
        this->applyForce(this->getDefaultAcc(), EAST);
        if((playerX-this->getDestination().x)<offset && playerY>this->getDestination().y)
        {
            setShouldFire(true);
        }
        else
        {
            setShouldFire(false);
        }
    }
    
    if(playerX<this->getDestination().x) /// keep 20 pixels north of player
    {
        this->applyForce(this->getDefaultAcc(), WEST);
        if((this->getDestination().x-playerX)<offset && playerY>this->getDestination().y)
        {
            setShouldFire(true);

        }
        else
        {
            setShouldFire(false);
        }
    }
    
}

bool EnemyDrone::getShouldFire()
{
    return shouldFire;
}
