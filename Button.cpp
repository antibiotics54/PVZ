//
//  Button.cpp
//  P_VS_Z
//
//  Created by Valeria Alfaro on 10/5/23.
//

#include "Button.h"
#include <SDL2/SDL.h>

#define botones "/Users/valeriaalfaro/Desktop/1173 progra III/P_VS_Z/assets/png/start&exit.png"


Button::Button(){
    static SDL_Texture * t = IMG_LoadTexture(ren, botones);
    tex = t;
    
    srect.h = 130;
    srect.w = 130;
    srect.x = 0;
    
    drect.h = 100;
    drect.w = 115;
    
    
}

Button::~Button(){
    
}

void Button::update(Mouse& mouse){
    
    if(SDL_HasIntersection(&drect, &mouse.point)){
        isSelected=true;
    }else{
        isSelected = false;
        srect.x = 0;
    }
}

void Button::draw(){
    SDL_RenderCopy(renderer, tex, &srect, &drect);
}
