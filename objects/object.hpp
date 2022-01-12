//
//  object.hpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/13.
//  Copyright © 2021 Jovian. All rights reserved.
//

#ifndef object_hpp
#define object_hpp

#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
class Object
{
public:
    Object()
    {
        
    }
    SDL_Rect getSource()
    {
        return source;
    }
    
    SDL_Rect getDestination()
    {
        return destination;
    }
    SDL_Texture* getTexture() const
    {
        return texture;
    }
    void setSelected(bool b)
    {
        selected = b;
    }
    bool isSelected()
    {
        return selected;
    }
    void draw(Object &object,SDL_Renderer *renderer);
    void setDestination(int x, int y, int width, int height);
    void setSource(int x, int y, int width, int height);
    void setImage(std::string filename, SDL_Renderer* renderer);
    void setImage(std::string filename);
private:
    SDL_Texture *texture;
    SDL_Rect source;
    SDL_Rect destination;
    bool selected;
    
};
#endif /* object_hpp */
