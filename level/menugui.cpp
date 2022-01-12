//
//  menugui.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/18.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "menugui.hpp"

enum
{
    MAIN_MENU,DOCK_MENU,MODIFY_MENU
};
void MenuGUI::initMenuGUI(SDL_Renderer* renderer,int &wW, int &wH,int displayM)
{
    displayMenu = displayM;
    menuGUIRenderer = renderer;
    setImage("screenv1.png", renderer);
    if(this->getTexture())
    {
        std::cout<<"loaded MenuGUI texture successfully"<<std::endl;
        
    }
    setSelected(false);
    windowWidth = wW;
    windowHeight = wH;
    setSource(0, 0, 500, 175);
    setDestination(windowWidth*.08, windowHeight*.15, windowWidth*.85, windowHeight*.2); //scales menu
    
    
    initGUI(windowWidth, windowHeight); //initializes fonts for menuGUI
    if(displayMenu == MAIN_MENU)
    {
        newGameButton.setSource(0, 0, 500, 100);
        newGameButton.setImage("newgame.png", renderer);
        newGameButton.setDestination(this->getDestination().x, this->getDestination().y, this->getDestination().w, this->getDestination().h/3);
        loadGameButton.setSource(0, 0, 500, 100);
        loadGameButton.setImage("loadgame.png", renderer);
        loadGameButton.setDestination(this->getDestination().x, this->getDestination().y+100, this->getDestination().w, this->getDestination().h/3);
        quitGameButton.setSource(0, 0, 500, 100);
        quitGameButton.setImage("quitgame.png", renderer);
        quitGameButton.setDestination(this->getDestination().x, this->getDestination().y+200, this->getDestination().w, this->getDestination().h/3);
        buttons.push_back(newGameButton);
        buttons.push_back(loadGameButton);
        buttons.push_back(quitGameButton);
    }
    if(displayMenu == DOCK_MENU)
    {
        
        modifyDroneButton.setSource(0, 0, 500, 100);
        modifyDroneButton.setImage("modifydrone.png", renderer);
        modifyDroneButton.setDestination(this->getDestination().x, this->getDestination().y, this->getDestination().w, this->getDestination().h/3);
        nextMissionButton.setSource(0, 0, 500, 100);
        nextMissionButton.setImage("nextmission.png", renderer);
        nextMissionButton.setDestination(this->getDestination().x, this->getDestination().y+100, this->getDestination().w, this->getDestination().h/3);
        exitToMainButton.setSource(0, 0, 500, 100);
        exitToMainButton.setImage("exittomain.png", renderer);
        exitToMainButton.setDestination(this->getDestination().x, this->getDestination().y+200, this->getDestination().w, this->getDestination().h/3);
        buttons.push_back(modifyDroneButton);
        buttons.push_back(nextMissionButton);
        buttons.push_back(exitToMainButton);
    }
    if(displayMenu == MODIFY_MENU)
    {
        
    }
    
    mousePointer.w = 10;
    mousePointer.h = 10;
 //   initAudio();

}


void MenuGUI::update()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
            {
                int mouseX = event.motion.x;
                int mouseY = event.motion.y;
                mousePointer.x = mouseX;
                mousePointer.y = mouseY;
                std::cout<<"Mouse X: "<<mouseX<<std::endl;
                for(int i = 0;i<buttons.size();i++)
                {
                    if(checkCollision(mousePointer, buttons[i].getDestination()))
                    {
                        std::cout<<"Overlapping on the buttons"<<std::endl;
                        buttons[i].setSelected(true);
                        setSelection(i);
                        playSound("click.wav",SDL_MIX_MAXVOLUME/2);
                    }
                    else
                    {
                        buttons[i].setSelected(false);

                    }
                }
            }
            break;
                
        }
    }
}

void MenuGUI::drawButtons()
{
    for(Object &b: buttons)
    {
        SDL_Rect destination = b.getDestination();
        SDL_Rect source = b.getSource();
        SDL_RenderCopyEx(menuGUIRenderer,b.getTexture(),&source,&destination,0,NULL,SDL_FLIP_NONE);
    }
}
void MenuGUI::clean()
{
    std::cout<<"Menu GUI cleaned successfully"<<std::endl;
    SDL_DestroyTexture(this->getTexture());
    
    for(Object o: buttons)
    {
        o.setSelected(false);
        
        SDL_DestroyTexture(o.getTexture());
    }
    buttons.clear();
  //  TTF_Quit();
}
