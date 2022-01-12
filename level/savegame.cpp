//
//  savegame.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/18.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "savegame.hpp"

Savegame::Savegame(Player* player)
{
  
    folderManager.saveGame(player);

}
