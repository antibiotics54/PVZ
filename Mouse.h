//
//  Mouse.h
//  P_VS_Z
//
//  Created by Valeria Alfaro on 10/5/23.
//

#ifndef Mouse_h
#define Mouse_h

class Mouse {
public:
    SDL_Texture * txt;
    SDL_Rect rect;
    SDL_Rect point;
    
    Mouse(){
        txt = IMG_LoadTexture(ren, "/Users/valeriaalfaro/Desktop/1173 progra III/P_VS_Z/assets/png/mouse-hand.png");
        rect.w = 25;
        rect.h = 25;
        point.w = 1;
        point.h = 1;
        SDL_ShowCursor(false);
    }
    
    void update(){
        SDL_GetMouseState(&rect.x, &rect.y);
        point.x = rect.x;
        point.y = rect.y;
    }
    
    void draw(){
        SDL_RenderCopy(renderer, txt, NULL, &rect);
    }
};


#endif /* Mouse_h */
