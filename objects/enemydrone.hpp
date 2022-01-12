//
//  enemydrone.hpp
//  dronewars
//
//  Created by mac on 2022/1/11.
//
// This class will just extend Object: entity
// This class adds simple AI to the entity
#ifndef enemydrone_hpp
#define enemydrone_hpp

#include <stdio.h>
#include "entity.hpp"
enum {
    TRASH_DRONE,UFO_DRONE
};

class EnemyDrone : public Entity
{
public:
    EnemyDrone()
    {
        
    }
//    ~EnemyDrone(); for some reason cant have destructor
    void update(int playerX,int playerY);
    void init(int dT, SDL_Renderer* renderer);
    void setShouldFire(bool b)
    {
        shouldFire = b;
    }
    bool getShouldFire();
private:
    int droneType;
    //// Animations //////
    int ufoDroneIdleAnim;
    int ufoDroneExplodeAmin;
    int trashDroneIdleAnim;
    int trashDroneExplodeAmin;
    ////// Animations End ///////
    int offset; //how far away the drone is from the player
    bool shouldFire; // determines when the drone should fire at the player
};
#endif /* enemydrone_hpp */
