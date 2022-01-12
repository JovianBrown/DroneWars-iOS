//
//  item.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/15.
//  Copyright © 2021 Jovian. All rights reserved.
//

#ifndef item_hpp
#define item_hpp


#include <stdio.h>
#include "object.hpp"
#include <vector>
#include "player.hpp"
enum ItemTypes
{
    RARE_ELEMENT,PRECIOUS_METAL,ENERGY_PULSE
};
class Item : public Object
{
public:
    Item()
    :active(true),speed(2)
    {
    }
    void init(SDL_Renderer* renderer,int type);
    bool getActive()
    {
        return active;
    }
    void setActive(bool b )
    {
        active = b;
    }
    const int getItemType()
    {
        return itemType;
    }
    const std::string getName()
    {
        return name;
    }
    void setItemType(int i)
    {
        itemType=i;
    }
    void update()
    {
        setDestination(getDestination().x, getDestination().y+speed, getDestination().w, getDestination().h);
        if(getDestination().y>1000)
            setActive(false);
    }
    void causeEffect(Player* player);
    
    int getValue();
    int speed;

private:
    int itemType; //rare_element Precious metal energy pulse
    bool active;
    int value; //how much you can trade the item for in credits
    std::vector <Item> items;
    std::string name;
};

#endif /* item_hpp */
