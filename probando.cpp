////
////  probando.cpp
////  PlantsZombies
////
////  Created by Valeria Alfaro on 27/5/23.
////
//
//#include "probando.hpp"
//#include <SDL2/SDL.h>
//#include <iostream>
//#include <cstdlib>
//#include <string>
//#include <sstream>
//#include <SDL2_image/SDL_image.h>
//#include <SDL2_ttf/SDL_ttf.h>
//using namespace std;
//
//#define zombie "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/ZombieWalkingSprites.png"
//#define flor "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/sunflower.png"
//#define pea "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/peashooters.png"
//#define walnut "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/roca1.png"
//#define iconP "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/icon_peashooter_100.png"
//#define dimIconP "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/icon_peashooter_100_dim.png"
//#define iconS "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/icon_sunflower.png"
//#define dimIconS "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/icon_sunflower_dim.png"
//#define iconW "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/icon_walnut.png"
//#define dimIconW "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/icon_walnut_dim.png"
//#define field "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/text_field.png"
//
//
//struct Icons {
//    bool is_sunflower_chosen ;
//    bool is_peashooter_chosen ;
//    bool is_walnut_chosen;
//};
//
//struct Blocks {
//    int x1, x2;
//    int y1, y2;
//};
//
//struct Suns {
//    int final_col;
//    int final_row;
//    int MoveOnY;
//    int wait_seconds;
//};
//
//struct Sunflowers {
//    int row, col;
//    int byte, vida;
//};
//
//struct Walnuts {
//    int row, col;
//    int byte, vida;
//    string directory;
//};
//
//struct Peashooters {
//    int row, col;
//    int byte, vida;
//};
//
//struct Peas {
//    int row;
//    int x_location;
//};
//
//struct Jugadors{
//    int sol_total;
//    string name;
//};
//
//struct Zombies {
//    int row;
//    int y_location;
//    int x_location;
//    int health;
//    bool moving;
//    string directory;
//};
//
//struct Objetos {
//    vector<Zombies> zombies;
//    vector<Peashooters> peashooter;
//    vector<Sunflowers> sunflower;
//    vector<Walnuts> walNut;
//    vector<Suns> suns;
//    vector<Peas> peas;
//};
//
//
////boolean para saber que icon fue seleccionado
//bool iconSelected(Icons &icon, int x,  int y){
//    if((y > 106) && (y < 195) && (x >50) && (x <110)){
//        icon.is_sunflower_chosen= true;
//        cout<<"SUNFLOWER SELECTED";
//        return true;
//    }else if((y > 234) && (y < 323) && (x>50) && (x<110)){
//        icon.is_walnut_chosen = true;
//        cout<<"WALNUT SELECTED";
//        return true;
//    }else if ((y > 170) && (y < 259) && (x>50) && (x<110)){
//        icon.is_peashooter_chosen = true;
//        cout<<"PEASHOOTER SELECTED";
//        return true;
//    }
//    return false;
//}
//
////boolean para crear plantas dependiendo del icon choosen
//void crearPlantas(Objetos &obj, Icons & icon, int &sol_total, int &x, int &y){
//    int row = y;
//    int col = x;
//    if((icon.is_peashooter_chosen) && (sol_total>=100)){
//        Peashooters ptemp;
//        ptemp.row = row;
//        ptemp.col = col;
//        obj.peashooter.push_back(ptemp);
//        sol_total -=100;
//        cout<<"Peashooter creado";
//    }else if((icon.is_sunflower_chosen) && (sol_total>=50)){
//        Sunflowers stemp;
//        stemp.row = row;
//        stemp.col = col;
//        obj.sunflower.push_back(stemp);
//        sol_total-=50;
//        cout<<"Sunflower creada";
//    }else if((icon.is_walnut_chosen) && (sol_total>=50)){
//        Walnuts wtemp;
//        wtemp.row = row;
//        wtemp.col = col;
//        obj.walNut.push_back(wtemp);
//        sol_total-=50;
//        cout<<"Walnt creada";
//    }
//}
//
////win.show_text(to_string(player.sun_count), 100, 33);
//
////funcion para mostrar txt
//void texto(SDL_Renderer* sprite, TTF_Font* font, int &soles){
//    SDL_Color color = {255, 255, 255};
//    string texto = to_string(soles);
//    SDL_Surface* textSurface = TTF_RenderText_Solid(font, texto.c_str(), color);
//    SDL_Texture* muestra = SDL_CreateTextureFromSurface(sprite, textSurface);
//    SDL_Rect textRect;
//    textRect.x = 5;
//    textRect.y = 5;
//    SDL_QueryTexture(muestra, nullptr, nullptr, &textRect.w, &textRect.h);
//    SDL_RenderCopy(sprite, muestra, nullptr, &textRect);
//    SDL_FreeSurface(textSurface);
//    SDL_DestroyTexture(muestra);
//}
//
//int main(int argc, char* argv[]){
//    SDL_Init(SDL_INIT_VIDEO);
//    IMG_Init(IMG_INIT_PNG);
//    // Initialize SDL_ttf
//        if ( TTF_Init() < 0 ) {
//            cout << "Error intializing SDL_ttf: " << TTF_GetError() << endl;
//            return 2;
//        }
//    SDL_StartTextInput();
//    string input;
//    Objetos Object;
//    Icons icon;
//    Jugadors player;
//    SDL_Texture* Texture, *t,  *dimP, *dimS, *dimW, *PeaIcon, *WalIcon, *SunIco, *texture;
//    SDL_Window* window = SDL_CreateWindow("YIPEEEEEE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
//    if(window==NULL){
//        cout<< "Error loading image: " << SDL_GetBasePath();
//        return 1;
//    }
//    SDL_Renderer* sprite = SDL_CreateRenderer(window, -1, 0);
//    SDL_Surface* temp = IMG_Load(field);
//    if (temp == NULL) {
//            cout<< "Error loading image: " << SDL_GetBasePath();
//            return 5;
//        }
//    Texture = SDL_CreateTextureFromSurface(sprite, temp);
//    SDL_SetRenderDrawColor(sprite, 255, 255, 255, 255);
//    bool quit=true;
//    int walkWidth, walkHeight;
//    int txtWidth=0, txtHeight=0;
//    const int moving = 60;
//    int frameTime =0;
//    SDL_Rect zWalk, position, pos, walking, dibujoPea, dibujoSun, dibujoWalnut;
//    SDL_QueryTexture(Texture, NULL, NULL, &txtWidth, &txtHeight);
//
//    /*
//     DIMENSIONES DEPENDIENDO DEL SPRITE
//     
//     ZOMBIE:
//     walkWidth = txtWidth/9;
//     walkHeight = txtHeight/1;
//     
//     PEASHOOTER:
//     walkWidth= txtWidth/8;
//     walkHeight = txtHeight/6;
//     
//     SUNFLOWER:
//     walkWidth= txtWidth/8;
//     walkHeight = txtHeight/2;
//     
//     */
//    walkWidth= txtWidth/8;
//    walkHeight = txtHeight/6;
//    
//    walking.x = walking.y =0;
//    zWalk.x = zWalk.y =0;
//    zWalk.h = walkHeight;
//    zWalk.w = walkWidth;
//    
//    position.x = position.y = 40;
//    position.w = position.h = 60;
//
//     int sol_total =145;
//    //crear las imagenes de los icons
//    SDL_Surface* pDim = IMG_Load(dimIconP);
//    SDL_Surface* p = IMG_Load(iconP);
//    SDL_Surface* sDim = IMG_Load(dimIconS);
//    SDL_Surface* sunflo = IMG_Load(iconS);
//    SDL_Surface* wDim = IMG_Load(dimIconW);
//    SDL_Surface* w = IMG_Load(iconW);
//    dimP = SDL_CreateTextureFromSurface(sprite, pDim);
//    PeaIcon = SDL_CreateTextureFromSurface(sprite, p);
//    dimS = SDL_CreateTextureFromSurface(sprite, sDim);
//    SunIco = SDL_CreateTextureFromSurface(sprite, sunflo);
//    dimW = SDL_CreateTextureFromSurface(sprite, wDim);
//    WalIcon = SDL_CreateTextureFromSurface(sprite, w);
//    int width =89, height = 60, iconX = 50, peaY = 167, walnutY = 231, sunY = 103;
// 
//    dibujoPea.x = iconX;
//    dibujoPea.y = peaY;
//    dibujoPea.w = width;
//    dibujoPea.h = height;
//    dibujoSun.x = iconX;
//    dibujoSun.y = sunY;
//    dibujoSun.w = width;
//    dibujoSun.h = height;
//    dibujoWalnut.x = iconX;
//    dibujoWalnut.y = walnutY;
//    dibujoWalnut.w = width;
//    dibujoWalnut.h = height;
//    
//    //verificacion de como aparecen
//   
//    TTF_Font* font = TTF_OpenFont("/Users/valeriaalfaro/Library/Fonts/35021733747.ttf", 33);
//    if ( !font ) {
//        cout << "Failed to load font: " << TTF_GetError() << endl;
//    }
//    int conta =0;
//    
//    while (quit) {
//        //sprites de zombieo
//        frameTime++;
//        if(moving/frameTime ==1){
//            frameTime =0;
////            cout<<"WALK WIDTH"<<walkWidth<<endl;
////            cout<<"WALK HEIGHT"<<walkHeight<<endl;
////            cout<<"TXT WIDTH"<<txtWidth<<endl;
////            cout<<"TXT HEIGHT"<<txtHeight<<endl;
//            cout<<endl<<endl;
//            walking.x += walkWidth;
//            zWalk.x += walkWidth;
//            if((zWalk.x > txtWidth) && (walking.x >= txtWidth)){
//                zWalk.x = 0;
//                walking.x = 0;
//            }
//        }
//        SDL_RenderClear(sprite);
//        //SDL_RenderCopy(sprite, Texture, &zWalk, &position);
//        
//        int x=0, y=0;
//        
//        if(sol_total < 50){
//            //display todo en dim
//            SDL_RenderCopy(sprite, dimP, NULL, &dibujoPea);
//            SDL_RenderCopy(sprite, dimS, NULL, &dibujoSun);
//            SDL_RenderCopy(sprite, dimW, NULL, &dibujoWalnut);
//        }else if (sol_total>=50){
//            //display solo las plantas sunflower y roca
//            SDL_RenderCopy(sprite, SunIco, NULL, &dibujoSun);
//            SDL_RenderCopy(sprite, WalIcon, NULL, &dibujoWalnut);
//            if(sol_total>=100){
//                //mostrar peashooter
//                SDL_RenderCopy(sprite, PeaIcon, NULL, &dibujoPea);
//            }else{
//                //poner el peashooter en dim
//                SDL_RenderCopy(sprite, dimP, NULL, &dibujoPea);
//            }
//        }
//        SDL_GetMouseState(&x, &y);
//       // cout<< x<< " : "<< y<<endl;
//        
//       
//        int row ,col;
//        SDL_Delay(30);
//        SDL_Event event;
//        SDL_PollEvent(&event);
//        bool mousePressed=false;
//        static const unsigned char* keys = SDL_GetKeyboardState( NULL );
//        switch (event.type) {
//        case SDL_QUIT:
//            quit = false;
//            break;
//        case SDL_MOUSEBUTTONDOWN:
//                if (event.button.button == SDL_BUTTON_LEFT) {
//                // Left mouse button clicked
//                x = event.button.x;
//                y = event.button.y;
//                    if(!mousePressed){
//                        cout<<"click"<<"   MOUSE X:"<<x;
//                        if(iconSelected(icon, x, y)){
//                            mousePressed = true;
//                            crearPlantas(Object, icon, sol_total, x, y);
//                        }
//                    }
//            }
//        default:
//            break;
//        }
//        
////        SDL_Color txt = {0,0,0};
////        pos.w =  65;
////        pos.h = 40;
////        pos.x = pos.y = 5;
////        // Render texture
////        SDL_RenderCopy(sprite, Texture, NULL, &pos);
////        
////        if ( input.size() ) {
////                SDL_Surface* text_surf = TTF_RenderText_Solid(font, input.c_str(), txt);
////                t = SDL_CreateTextureFromSurface(sprite, text_surf);
////            SDL_Rect dest;
////                dest.x = 7 - (text_surf->w / 2.0f);
////                dest.y = 5;
////                dest.w = text_surf->w+10;
////                dest.h = text_surf->h;
////                SDL_RenderCopy(sprite, t, NULL, &dest);
////        
////                SDL_DestroyTexture(t);
////                SDL_FreeSurface(text_surf);
////            }
//        
////        for (int a =0; a<Object.walNut.size();a++){
////            SDL_Surface* temp = IMG_Load(walnut);
////            texture = SDL_CreateTextureFromSurface(sprite, temp);
////            if (temp == NULL ) {
////                cout << "Error loading image: " << SDL_GetBasePath();
////                return 10;
////            }
////            SDL_Rect Espacio;
////            Espacio.x = Object.walNut[a].col;
////            Espacio.y = Object.walNut[a].row;
////            SDL_RenderCopy(sprite, texture, &zWalk, &Espacio);
////        }
//        if(x<=20){
//            sol_total+=50;
//            cout<<"Sol totales: "<<sol_total<<endl;
//        }
//        texto(sprite, font, sol_total);
//        SDL_RenderPresent(sprite);
//        
//    }
//    SDL_FreeSurface(temp);
//    SDL_DestroyWindow(window);
//    SDL_RenderClear(sprite);
//    IMG_Quit();
//    SDL_Quit();
//    TTF_Quit();
//}
