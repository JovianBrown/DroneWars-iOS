//
//  loadgame.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/18.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "loadgame.hpp"
Loadgame::Loadgame()
{
    /// acquire player info from fm service
    std::string playerInfo = folderManager.loadGame();
    std::cout<<"Player data from stored file: "<<std::endl;

    seperateStringBySpace(playerInfo);
    if(playerStats.size()>0)
    {
        std::cout<<"Player stats [0] "<<playerStats[0];
        std::cout<<"Player stats [1] "<<playerStats[1];
        std::cout<<"Player stats [2] "<<playerStats[2];
        std::cout<<"Player stats [10] "<<playerStats[10];


    }
    else
    {
        std::cout<<"Unable to load player file"<<std::endl;

    }
}
/// to format string properly separate by spaces
void Loadgame::seperateStringBySpace(string str)
{
    string word = "";
    for (auto x : str)
    {
        if (x == ' ')
        {
            cout << word << endl;
            playerStats.push_back(word);
            word = "";
        }
        else {
            word = word + x;
        }
    }
}
vector<string> Loadgame::getPlayerStats()
{
    
    return playerStats;
    
}
