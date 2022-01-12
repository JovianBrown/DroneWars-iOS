//
//  alert.hpp
//  dronewars
//
//  Created by mac on 2022/1/7.
//

#ifndef alert_hpp
#define alert_hpp

#include <stdio.h>
#include "object.hpp"
#include "timer.hpp"
#include <vector>
class Alert
{
  
    public:
        void updateAlerts();
        Alert(SDL_Renderer* renderer);
        void addAlert(int alertType);
        void drawAlerts(SDL_Renderer* renderer);
        ~Alert();
    private:
        Timer* alertTimer;
        std::vector <Timer*> alertTimers;
        int alertType;
        ////// Alert Objects for Display //////
        Object lowShield;
        Object hullDamage;
        std::vector <Object> alertObjects;
};
#endif /* alert_hpp */
