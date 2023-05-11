//
//  Button.h
//  P_VS_Z
//
//  Created by Valeria Alfaro on 10/5/23.
//

#ifndef Button_h
#define Button_h

//#include <SDL2/SDL_render.h>
#include "Mouse.h"


class Button{
public:
    SDL_Texture * tex;
    SDL_Rect srect, drect;
    bool isSelected = false;
    Button();
    virtual ~Button();
    
    void update(Mouse&);
    void draw();
};

#endif /* Button_h */
