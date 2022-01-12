//
//  alert.cpp
//  dronewars
//
//  Created by mac on 2022/1/7.
//

#include "alert.hpp"

enum ALERT_TYPES
{
    LOW_SHIELDS=1,HULL_DAMAGE
};

Alert::Alert(SDL_Renderer* renderer)
{
    lowShield.setImage("shieldalert.png", renderer);
    lowShield.setSource(0, 0, 400, 100);
    lowShield.setDestination(0, 0, 400, 100);
    
    hullDamage.setImage("hullalert.png", renderer);
    hullDamage.setSource(0, 0, 400, 100 );
    hullDamage.setDestination(0, 0, 400, 100);
    alertObjects.push_back(lowShield);
    alertObjects.push_back(hullDamage);
}
void Alert::addAlert(int alertType)
{
    
    alertTimer = new Timer;
    alertTimer->setTimerActive(true);
    if(alertType == LOW_SHIELDS)
    {
        alertTimer->setDuration(3000);
        this->alertType=1;
    }
    if(alertType == HULL_DAMAGE)
    {
        alertTimer->setDuration(3000);
        this->alertType=2;
    }
    
    alertTimers.push_back(alertTimer);
}
void Alert::updateAlerts()
{
    if(alertTimers.size()>0)
    {
        for(Timer *t: alertTimers)
        {
            t->update();
            if(!t->isActive())
            {
                
            }
        }
        
    }
}
void Alert::drawAlerts(SDL_Renderer* renderer)
{
    if(alertTimers.size()>0)
    {
        for(Timer *t: alertTimers)
        {
            if(t->isActive())
            {
                if(this->alertType==1)
                {
                    lowShield.draw(lowShield,renderer);
                }
                if(this->alertType==2)
                {
                    hullDamage.draw(hullDamage,renderer);
                }
            }
        }
    }
    
}

Alert::~Alert()
{
    for(Timer *t: alertTimers)
    {
        t->setTimerActive(false);
    }
    alertTimers.clear();
    alertObjects.clear();
    SDL_DestroyTexture(lowShield.getTexture());
    SDL_DestroyTexture(hullDamage.getTexture());

}
