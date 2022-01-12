//
//  menugui.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/18.
//  Copyright © 2021 Jovian. All rights reserved.
//
// could modify this class and hud to share inherit a basic class that implements text
//maybe inherit twice, one from object : GUI : dockMenu etc
#ifndef menugui_hpp
#define menugui_hpp

#include <stdio.h>
#include <iostream>
#include "SDL.h"
//#include "SDL_image.h"
//#include "SDL_ttf.h"
#include "gui.hpp"
#include <vector>
#include "common.hpp"
#include "audio.hpp"

class MenuGUI : public GUI
{
public:
    MenuGUI()
    :x(0),y(0),width(500),height(175),selection(-1)
    {
    }
    void initMenuGUI(SDL_Renderer* renderer,int &windowWidth,int &windowHeight,int displayM);
    void update();
    void drawButtons();
    const int getSelection() const
    {
        return selection;
    }
    void setSelection(int s)
    {
        selection = s;
    }
    void clean();
private:
    
    
    int x,y,width,height;
    int windowWidth,windowHeight;
    int menuWidth,menuHeight; 
    int selection; //which button was clicked on
    int displayMenu; /// which menu buttons to load and display
    
    /////// Buttons for Main Menu  //////////
    Object newGameButton;
    Object loadGameButton;
    Object quitGameButton;
    ///////////////////////////
    //// Buttons for Dock Menu /////
    Object nextMissionButton;
    Object exitToMainButton;
    Object modifyDroneButton;
    ////////// /////////
    std::vector <Object> buttons;
    SDL_Renderer* menuGUIRenderer;
    SDL_Rect mousePointer;

  //  bool checkCollision(SDL_Rect rectA, SDL_Rect rectB);

};
#endif /* menugui_hpp */
