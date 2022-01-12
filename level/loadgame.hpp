//
//  loadgame.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/18.
//  Copyright © 2021 Jovian. All rights reserved.
//

#ifndef loadgame_hpp
#define loadgame_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "foldermanager.hpp"
using namespace std;

class Loadgame
{
public:
    Loadgame();
    vector<string> getPlayerStats();
private:
    vector<string> playerStats;
    fm::FolderManager folderManager;
    void seperateStringBySpace(string str);
};
#endif /* loadgame_hpp */
