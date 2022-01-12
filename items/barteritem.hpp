//
//  barteritem.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/27.
//  Copyright © 2021 Jovian. All rights reserved.
//
// this class will consist of the items that will be available for purchase such as hull modifications
// blaster and other modifications

#ifndef barteritem_hpp
#define barteritem_hpp

#include <stdio.h>
#include "object.hpp"
enum BarterItemTypes
{
    BLASTER_BLUE,BLASTER_WIDE_GREEN

};

class BarterItem : public Object
{
    public:
        int getBarterItemType();
        void init(SDL_Renderer* renderer,int barterItemType);
        int getCost();
        const std::string getBarterItemName();
    private:
    int cost;  //cost to the player in credits
    int barterItemType;
    std::string barterItemName;
};

#endif /* barteritem_hpp */
