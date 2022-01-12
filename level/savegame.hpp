//
//  savegame.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/18.
//  Copyright © 2021 Jovian. All rights reserved.
//

#ifndef savegame_hpp
#define savegame_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>
#include "player.hpp"
#include "foldermanager.hpp"

class Savegame {
    
public:
    Savegame(Player* player);
    
private:
    fm::FolderManager folderManager;
};
#endif /* savegame_hpp */
