//
//  item.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/15.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "item.hpp"

void Item::init(SDL_Renderer* renderer,int type)
{
    this->setSource(0, 0, 300, 300);
   
    if(type == RARE_ELEMENT)
    {
        
        this->setImage("rareelementv1.png", renderer);
        this->value = 15;
        itemType=RARE_ELEMENT;
        this->name = "Rare Element";
        
    }
    if(type == PRECIOUS_METAL)
    {
        this->setImage("preciousmetal.png", renderer);
        this->value = 10;
        itemType=PRECIOUS_METAL;
        this->name = "Metal Alloy";

    }
    if(type == ENERGY_PULSE)
    {
        this->setImage("energypulse.png", renderer);
        this->value = 10;
        itemType = ENERGY_PULSE;
        this->name = "Energy Pulse";

    }
    
    
}
int Item::getValue()
{
    return value;
}
void Item::causeEffect(Player* player)
{
    
    if(itemType == RARE_ELEMENT)
    {
        int randomValue = rand()%10;
        player->setRareElements(player->getRareElements()+randomValue);
    }
    if(itemType == PRECIOUS_METAL)
    {
        int randomValue = rand()%10;
        player->setPreciousMetals(player->getPreciousMetals()+randomValue);
    }
    if(itemType == ENERGY_PULSE)
    {
        int randomValue = rand()%20;
        if(player->getShield()>0 && player->getShield()<=player->getMaxShield())
        {
            player->setShield(player->getShield()+randomValue);
        }
        else
        {
            player->setHps(player->getHps()+randomValue);
        }
        
    }
}

