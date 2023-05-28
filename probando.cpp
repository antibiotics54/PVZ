//
//  probando.cpp
//  PlantsZombies
//
//  Created by Valeria Alfaro on 27/5/23.
//

#include "probando.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2_image/SDL_image.h>
using namespace std;

#define zombie "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/sunflower.png"


int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_Texture* Texture;
    SDL_Window* window = SDL_CreateWindow("YIPEEEEEE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* sprite = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface* temp = IMG_Load(zombie);
    if (temp == NULL) {
            cout<< "Error loading image: " << SDL_GetBasePath();
            return 5;
        }
    Texture = SDL_CreateTextureFromSurface(sprite, temp);
    SDL_FreeSurface(temp);
    SDL_SetRenderDrawColor(sprite, 255, 255, 255, 255);
    bool quit=true;
    const int moving = 60;
    int frameTime = 0;
    int walkWidth, walkHeight;
    int txtWidth=0, txtHeight=0;
    SDL_Rect zWalk, position;
    SDL_QueryTexture(Texture, NULL, NULL, &txtWidth, &txtHeight);

    /*
     DIMENSIONES DEPENDIENDO DEL SPRITE
     
     ZOMBIE:
     walkWidth = txtWidth/7;
     walkHeight = txtHeight/1;
     
     PEASHOOTER:
     walkWidth= txtWidth/8;
     walkHeight = txtHeight/6;
     
     SUNFLOWER:
     walkWidth= txtWidth/8;
     walkHeight = txtHeight/2;
     
     */
    walkWidth= txtWidth/8;
    walkHeight = txtHeight/2;

    position.x = position.y =50;
    position.w = position.h = 50;
    zWalk.x = zWalk.y =0;
    zWalk.h = walkHeight;
    zWalk.w = walkWidth;

    while (quit) {
        //sprites de zombie
        frameTime++;

        if(moving/frameTime == 1){
            frameTime =0;
            zWalk.x += walkWidth;
            if(zWalk.x >= txtWidth){
                zWalk.x = 0;
            }
        }

        SDL_RenderClear(sprite);
        SDL_RenderCopy(sprite, Texture, &zWalk, NULL);
        SDL_RenderPresent(sprite);
        SDL_Delay(5);
        SDL_Event event;
        SDL_PollEvent(&event);

        switch (event.type) {
        case SDL_QUIT:
            quit = false;
            break;
        default:
            break;
        }

    }
    SDL_Quit();

}
