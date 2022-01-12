//
//  barteritem.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/27.
//  Copyright © 2021 Jovian. All rights reserved.
//
#include "barteritem.hpp"


void BarterItem::init(SDL_Renderer *renderer, int barterItemType)
{

   if(barterItemType ==  BLASTER_BLUE)
   {
       this->setSource(0, 0, 100, 100);

       this->barterItemType = barterItemType;
       this->setImage("bluelaserwide.png", renderer);
       this->cost = 50;
       this->barterItemName = "Blue Blaster";
   }
    if(barterItemType ==  BLASTER_WIDE_GREEN)
    {
        this->setSource(0, 0, 200, 100);

        this->setImage("greenlaserwide.png", renderer);
        this->cost = 100;
        this->barterItemType = barterItemType;
        this->barterItemName = "Green Blaster";

        
    }
}
const std::string BarterItem::getBarterItemName()
{
    return barterItemName;
}

int BarterItem::getCost()
{
    return cost;
}
int BarterItem::getBarterItemType()
{
    return barterItemType;
}

