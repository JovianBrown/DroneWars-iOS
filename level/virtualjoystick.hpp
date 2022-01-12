//
//  virtualjoystick.hpp
//  dronewars
//
//  Created by mac on 2022/1/2.
//

#ifndef virtualjoystick_hpp
#define virtualjoystick_hpp

#include <stdio.h>
#include "object.hpp"
#include <vector>
//#include "playstate.hpp"
//class PlayState; // make sure this class knows about the Playstate class.

class VirtualJoystick
{
  
    public:
    VirtualJoystick(SDL_Renderer* renderer,int windowWidth,int windowHeight)
    :x(0),y(850)
    {
        joyStickRenderer = renderer;
        
        
/*        joyStickBase.setImage("joystickbase.png", renderer);
        joyStickBase.setSource(0, 0, 150, 150);
        joyStickBase.setDestination(0, 850, 120, 120);
        
        joyStickTop.setImage("joysticktop.png", renderer);
        joyStickTop.setSource(0, 0, 150, 150);
        joyStickTop.setDestination(0, 850, 120, 120); */
        
        /* need references to joystick rectangles for rendering */
        /*     baseDestination = joyStickBase.getDestination();
         baseSource = joyStickBase.getSource();
         topDestination = joyStickTop.getDestination();
         topSource = joyStickTop.getSource(); */
        
        
        joyStickButtonA.setImage("joystickbuttonA.png", joyStickRenderer);
        joyStickButtonA.setSource(0, 0, 150, 150);
        joyStickButtonA.setDestination(500, 850, 120, 120);
       
        joyStickButtonB.setImage("joystickbuttonB.png", joyStickRenderer);
        joyStickButtonB.setSource(0, 0, 150, 150);
        joyStickButtonB.setDestination(650, 850, 120, 120);
        
        joyStickLeft.setImage("joysticktop.png", joyStickRenderer);
        joyStickLeft.setSource(0, 0, 150, 150);
        joyStickLeft.setDestination(0, 800, 150, 150);
        
        joyStickRight.setImage("joysticktop.png", joyStickRenderer);
        joyStickRight.setSource(0, 0, 150, 150);
        joyStickRight.setDestination(200, 800, 150, 150);
                                     
        joyStickUp.setImage("joysticktop.png",joyStickRenderer);
        joyStickUp.setSource(0, 0, 150, 150);
        joyStickUp.setDestination(100, 700, 150, 150);

        joyStickDown.setImage("joysticktop.png",joyStickRenderer);
        joyStickDown.setSource(0, 0, 150, 150);
        joyStickDown.setDestination(100, 900, 150, 150);
        
        buttons.push_back(joyStickButtonA);
        buttons.push_back(joyStickButtonB);
        buttons.push_back(joyStickLeft);
        buttons.push_back(joyStickRight);
        buttons.push_back(joyStickUp);
        buttons.push_back(joyStickDown);

        mousePointer.w = 10;
        mousePointer.h = 10;
  
        buttonADest = joyStickButtonA.getDestination();
        buttonASource = joyStickButtonA.getSource();
        buttonBDest = joyStickButtonB.getDestination();
        buttonBSource = joyStickButtonB.getSource();
        
        buttonRightDest = joyStickRight.getDestination();
        buttonRightSource = joyStickRight.getSource();
        
        buttonLeftDest = joyStickLeft.getDestination();
        buttonLeftSource = joyStickLeft.getSource();
        
        buttonUpDest = joyStickUp.getDestination();
        buttonUpSource = joyStickUp.getSource();
        
        buttonDownDest = joyStickDown.getDestination();
        buttonDownSource = joyStickDown.getSource();

    }
    ~VirtualJoystick();
    void draw();
    void update();
    bool checkCollision(SDL_Rect rectA, SDL_Rect rectB);
    int getSelection()
    {
        return buttonPressed;
    }
    const int getDirection() const
    {
        return direction;
    }
    void setSelection(int i)
    {
        buttonPressed = i;
    }
    private:
        int x;
        int y;
        int windowWidth;
        int windowHeight;
//    Object joyStickBase;
//    Object joyStickTop;
    Object joyStickUp;
    Object joyStickDown;
    Object joyStickLeft;
    Object joyStickRight;
    Object joyStickButtonA;
    Object joyStickButtonB;

    SDL_Renderer* joyStickRenderer;
    SDL_Rect mousePointer;
    std::vector <Object> buttons;
    int buttonPressed;
    int direction;
    
    
 /*   SDL_Rect baseDestination;
    SDL_Rect baseSource;
    SDL_Rect topDestination;
    SDL_Rect topSource; */
    SDL_Rect buttonRightDest;
    SDL_Rect buttonRightSource;
    SDL_Rect buttonLeftDest;
    SDL_Rect buttonLeftSource;
    SDL_Rect buttonUpSource;
    SDL_Rect buttonUpDest;
    SDL_Rect buttonDownSource;
    SDL_Rect buttonDownDest;

    SDL_Rect buttonADest;
    SDL_Rect buttonASource;
    SDL_Rect buttonBDest;
    SDL_Rect buttonBSource;
};
#endif /* virtualjoystick_hpp */
