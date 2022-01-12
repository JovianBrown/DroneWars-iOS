//
//  missionbriefgui.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/21.
//  Copyright © 2021 Jovian. All rights reserved.
//

#ifndef missionbriefgui_hpp
#define missionbriefgui_hpp

#include <stdio.h>
#include "gui.hpp"

// this class is used to display just the hud graphic for briefstate.cpp
class MissionBriefGUI : public GUI
{
public:
    MissionBriefGUI()
    {
    }
    ~MissionBriefGUI();
    void init(SDL_Renderer* renderer);
private:
    SDL_Renderer* briefRenderer;
    
};
#endif /* missionbriefgui_hpp */
