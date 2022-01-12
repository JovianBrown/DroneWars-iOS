//
//  enemyprojectile.hpp
//  dronewars
//
//  Created by mac on 2022/1/11.
//

#ifndef enemyprojectile_hpp
#define enemyprojectile_hpp

#include <stdio.h>
#include "object.hpp"
class EnemyProjectile: public Object
{
public:
    void init(int projectileType, SDL_Renderer* renderer);
    void update();
    void setActive(bool b)
    {
        this->active = b;
    }
    bool isActive()
    {
        return active;
    }
    int getType()
    {
        return type;
    }
    const int getDamage() const
    {
        return damage;
    }
    const std::string getName() const
    {
        return name;
    }
    
private:
    int projectileType;
    int type;
    int speed;
    int damage;
    int projectileBehavior;
    std::string name;
    bool active;
};

#endif /* enemyprojectile_hpp */
