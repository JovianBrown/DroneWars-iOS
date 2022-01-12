//
//  virtualjoystick.cpp
//  dronewars
//
//  Created by mac on 2022/1/2.
//

#include "virtualjoystick.hpp"

enum   //Enum used for calling by playstate. playstate calls getDirection()
{
    MOVE_LEFT=1,MOVE_RIGHT,MOVE_UP,MOVE_DOWN
};

void VirtualJoystick::draw()
{
 
    SDL_RenderCopyEx(joyStickRenderer,joyStickLeft.getTexture(),&buttonLeftSource,&buttonLeftDest,0,NULL,SDL_FLIP_NONE);
      SDL_RenderCopyEx(joyStickRenderer,joyStickRight.getTexture(),&buttonRightSource,&buttonRightDest,0,NULL,SDL_FLIP_NONE);
       SDL_RenderCopyEx(joyStickRenderer,joyStickButtonA.getTexture(),&buttonASource,&buttonADest,0,NULL,SDL_FLIP_NONE);
     SDL_RenderCopyEx(joyStickRenderer,joyStickButtonB.getTexture(),&buttonBSource,&buttonBDest,0,NULL,SDL_FLIP_NONE);
    SDL_RenderCopyEx(joyStickRenderer,joyStickUp.getTexture(),&buttonUpSource,&buttonUpDest,0,NULL,SDL_FLIP_NONE);
    SDL_RenderCopyEx(joyStickRenderer,joyStickDown.getTexture(),&buttonDownSource,&buttonDownDest,0,NULL,SDL_FLIP_NONE);

}
bool VirtualJoystick::checkCollision(SDL_Rect rectA, SDL_Rect rectB)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    //Calculate the sides of rect A
    leftA = rectA.x;
    rightA = rectA.x + rectA.w;
    topA = rectA.y;
    bottomA = rectA.y + rectA.h;
    
    //Calculate the sides of rect B
    leftB = rectB.x;
    rightB = rectB.x + rectB.w;
    topB = rectB.y;
    bottomB = rectB.y + rectB.h;
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}
void VirtualJoystick::update()
{
    SDL_Event event;
    
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        
            case SDL_MOUSEBUTTONDOWN:
            {
           
                mousePointer.x = event.motion.x;
                mousePointer.y = event.motion.y;
                for(int i = 0; i < buttons.size();i++)
                {
                    if(checkCollision(buttons[i].getDestination(), mousePointer))
                    {
                        buttons[i].setSelected(true);
                        setSelection(i+1);
                       // std::cout<<"Button Pressed : "<<buttonPressed<<std::endl;
                                            
                    }
            /*        else
                    {
                        buttons[i].setSelected(false);
                    }   */
                }
            }
            break;
            case SDL_MOUSEBUTTONUP:
            {
                for(int i = 0; i < buttons.size();i++)
                {
                      buttons[i].setSelected(false);
                }
            }
            break;
        }
    }
}

      /*      case SDL_MOUSEMOTION:
            {
                static int xpos = windowWidth / 2; // = 400 to center the cursor in the window
                static int ypos = windowHeight / 2; // = 300 to center the cursor in the window
                xpos += event.motion.xrel;
                ypos += event.motion.yrel;
     
                if(event.motion.xrel>1)
                {
                    direction=MOVE_RIGHT;
                    std::cout<<"move player right: "<<event.motion.xrel<<std::endl;
                    
                }
                if(event.motion.xrel<0)
                {
                    direction=MOVE_LEFT;
                    std::cout<<"move player left: "<<event.motion.xrel<<std::endl;
                    
                }
                if(event.motion.yrel<0)
                {
                    direction=MOVE_UP;
                    std::cout<<"move player up: "<<event.motion.xrel<<std::endl;
                    
                }
                if(event.motion.yrel>1)
                {
                    direction=MOVE_DOWN;
                    std::cout<<"move player down:  "<<event.motion.xrel<<std::endl;

                }
                else
                {
                    direction = 0;
                }
                
                
            }
            break; */
      /* case SDL_MOUSEMOTION:
                 {
                 if(event.motion.xrel>0)
                 {
                 direction=MOVE_RIGHT;
                 std::cout<<"move player right"<<event.motion.xrel<<std::endl;
                 
                 }
                 if(event.motion.xrel<0)
                 {
                 direction=MOVE_LEFT;
                 std::cout<<"move player left"<<event.motion.xrel<<std::endl;
                 
                 }
                 if(event.motion.yrel<0)
                 {
                 direction=MOVE_UP;
                 std::cout<<"move player up"<<event.motion.xrel<<std::endl;
                 
                 }
                 if(event.motion.yrel>0)
                 {
                 direction=MOVE_DOWN;
                 }
                 
                 }
                 break;  */
VirtualJoystick::~VirtualJoystick()
{
    std::cout<<"Called VirtualJoystick Destructor "<<std::endl;
    buttons.clear();
   // SDL_DestroyTexture(joyStickTop.getTexture());
   // SDL_DestroyTexture(joyStickBase.getTexture());
    SDL_DestroyTexture(joyStickLeft.getTexture());
    SDL_DestroyTexture(joyStickRight.getTexture());
    SDL_DestroyTexture(joyStickUp.getTexture());
    SDL_DestroyTexture(joyStickDown.getTexture());

    SDL_DestroyTexture(joyStickButtonA.getTexture());
    SDL_DestroyTexture(joyStickButtonB.getTexture());

}
