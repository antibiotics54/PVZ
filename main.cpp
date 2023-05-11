//
//  main.cpp
//  P_VS_Z
//
//  Created by Valeria Alfaro on 6/5/23.
//
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

char *mensaje;
char *composition;

int main(int argc, char** argv) {
    bool quit = true;
    SDL_Event evento;
    
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Window *window = SDL_CreateWindow("PVZ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface *image = SDL_LoadBMP("/Users/valeriaalfaro/Desktop/1173 progra III/P_VS_Z/assets/bmp/fondo_login.bmp");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_StartTextInput();
    while(quit){
        SDL_WaitEvent(&evento);
        
        switch(evento.type){
            case SDL_QUIT:
                quit = false;
                break;
            case SDL_TEXTINPUT:
                strcat(mensaje, evento.text.text);
                break;
            case SDL_TEXTEDITING:
                composition = evento.edit.text;
                break;
        }
        
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
    
    SDL_Quit();
    
    return 0;
    
    
//    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//
//    SDL_RenderClear(renderer);
//
//    SDL_RenderPresent(renderer);
    //SDL_Delay(3000);
}
