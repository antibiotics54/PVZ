
#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <ctime>
#include <vector>
#include "Mouse.h"
#include <SDL2_image/SDL_image.h>
using namespace std;

SDL_Texture* Texture, * Fondo, *inicio, *solContador, *dimP, *dimS, *dimW, *PeaIcon, *WalIcon, *SunIcon, *Txt;
SDL_Rect space, Image,cuadro, zWalk, guisante, Espacio, movePea, dibujoPea, dibujoSun, dibujoWalnut, danger, moveWalnut, moveSunflower, pos, solPos;
int walkWidth, txtWidth;

#define zombie "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/ZombieWalkingSprites.png"
#define pelota "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/pea.png"
#define sunny "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/sun.png"
#define patio "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/Patio.png"
#define flor "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/sunflower.png"
#define pea "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/peashooters_copy.png"
#define iconP "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/icon_peashooter_100.png"
#define dimIconP "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/icon_peashooter_100_dim.png"
#define iconS "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/icon_sunflower.png"
#define dimIconS "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/icon_sunflower_dim.png"
#define iconW "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/icon_walnut.png"
#define dimIconW "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/icon_walnut_dim.png"
#define pegar "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/impacto.png"
#define walNut "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/roca_copy.png"
#define login "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/fondo_login.png"
#define danger1 "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/danger1.png"
#define comiendo "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/comiendo.png"

//defini aqui arriba mis dirrectorios porque en mac es distinto


//structs que son como clases
struct Icons {
    bool is_sunflower_chosen ;
    bool is_peashooter_chosen ;
    bool is_walnut_chosen;
//    string sunflower_icon_directory;
//    string peashooter_icon_directory;
//    string walnut_icon_directory;
};

struct Block {
    int x1, x2;
    int y1, y2;
};

struct Sun {
	int final_col;
	int final_row;
	int MoveOnY;
	int wait_seconds;
};

struct Sunflower {
	int row, col;
	int byte, vida;
};

struct Walnut {
	int row, col;
	int byte, vida;
	string directory;
};

struct Peashooter {
	int row, col;
	int byte, vida;
};

struct Pea {
	int row;
	int x_location;
};

struct Jugador{
    int sol_total;
    string name;
};

struct Zombie {
	int row;
	int y_location;
	int x_location;
	int health;
	bool moving;
	string directory;
};

struct Objetos {
    vector<Zombie> zombies;
    vector<Peashooter> peashooter;
    vector<Sunflower> sunflower;
    vector<Walnut> walnut;
    vector<Sun> suns;
    vector<Pea> peas;
};


vector<vector<Block> > Screen;

//este void crea los peashooters en posicion definida (prototipo)
void crearPeashooters(Objetos &obj) {
    Peashooter temp;
    temp.col = 270;
    temp.row = 84;
    obj.peashooter.push_back(temp);
    Peashooter temp1;
    temp1.col = 270;
    temp1.row = 178;
    obj.peashooter.push_back(temp1);
    Peashooter temp2;
    temp2.col = 270;
    temp2.row = 278;
    obj.peashooter.push_back(temp2);
    Peashooter temp3;
    temp3.col = 270;
    temp3.row = 381;
    obj.peashooter.push_back(temp3);
    Peashooter temp4;
    temp4.col = 270;
    temp4.row = 473;
    obj.peashooter.push_back(temp4);
    std::cout << "Creado";
    
}

void crearWalnuts(Objetos &obj) {
    Walnut temp;
    temp.col = 540;
    temp.row = 84;
    obj.walnut.push_back(temp);
    Walnut temp1;
    temp1.col = 540;
    temp1.row = 178;
    obj.walnut.push_back(temp1);
    Walnut temp2;
    temp2.col = 540;
    temp2.row = 278;
    obj.walnut.push_back(temp2);
    Walnut temp3;
    temp3.col = 540;
    temp3.row = 381;
    obj.walnut.push_back(temp3);
    Walnut temp4;
    temp4.col = 540;
    temp4.row = 473;
    obj.walnut.push_back(temp4);
    std::cout << "Creado";
    
}

//crear el board desde la imagen
vector<vector<Block> > Create_Board() {
    vector<vector<Block> > result;
    vector<Block> temps;
    Block temp;
    for (int y = 0; y < 5; y++) {
        temps.clear();
        for (int x = 0; x < 9; x++) {
            temp.x1 = 257 + (x * 78);
            temp.x2 = 257 + ((x + 1) * 78);
            temp.y1 = 80 + (y * 97);
            temp.y2 = 80 + ((y + 1) * 97);

            temps.push_back(temp);
        }
        result.push_back(temps);
    }
    return result;
}

//verificacion si se puede mover el zombie
bool ZombiePuedeMoverse(Zombie zomb, int row, int col, vector<vector<Block> >& map) {
    int right_limit = map[row][col].x2 - 35;
    int left_limit = map[row][col].x1;
    int zombie_new_location = zomb.x_location - 1;
    if (zomb.row == row && zombie_new_location < right_limit && zombie_new_location > left_limit)
        return true;
    return false;
}

//verificar si el zombie choco con la planta
bool ZombieChocadoConPlantas(Objetos& elements, Zombie& zomb, vector<vector<Block> >& map) {
    for (int i = 0; i < elements.walnut.size(); i++) {
        if (ZombiePuedeMoverse(zomb, elements.walnut[i].row, elements.walnut[i].col, map)) {
            zomb.moving = false;
            return true;
        }
    }
    for (int i = 0; i < elements.peashooter.size(); i++) {
        if (ZombiePuedeMoverse(zomb, elements.peashooter[i].row, elements.peashooter[i].col, map)) {
            zomb.moving = false;
            return true;
        }
    }
    for (int i = 0; i < elements.sunflower.size(); i++) {
        if (ZombiePuedeMoverse(zomb, elements.sunflower[i].row, elements.sunflower[i].col, map)) {
            zomb.moving = false;
            return true;
        }
    }
    zomb.moving = true;
    return false;
}

//verificar si el zombie se creo en la misma fila que el peashooter
bool IsZombieInPeashooterRow(Peashooter peashooter, Zombie zomb) {
    if (zomb.y_location == peashooter.row) {
        return true;
    }
    return false;
}

//verificar si el zombie esta en la posicion de la pea
bool IsZombieInPeaRow(Pea peas, Zombie zomb) {
    if (zomb.y_location+5 == peas.row) {
        return true;
    }
    return false;
}

//verificacion de zombie golpeado
bool PeaGolpeadoZombie(Pea peas, Zombie zomb) {
    if (zomb.x_location <= peas.x_location)
        return true;
    return false;
}

//
void apply_pea_hitting_zombie(Objetos& elements, int p_ind, int z_ind) {
    if (PeaGolpeadoZombie(elements.peas[p_ind], elements.zombies[z_ind])) {
        elements.zombies[z_ind].health--;
        elements.peas.erase(elements.peas.begin() + p_ind);
        if (elements.zombies[z_ind].health == 0)
            elements.zombies.erase(elements.zombies.begin() + z_ind);
    }
}

//funcion para crear pea
void crear_Pea(int col,int row, Objetos& obj) {
    Pea temp;
    temp.row = col+5;
    temp.x_location = row+35;
    obj.peas.push_back(temp);
}

//funcion para crear pea dependiendo de la posicion
void mostrarPea(Objetos& obj, SDL_Renderer* ren) {
    for (int gus = 0; gus < obj.peas.size(); gus++) {
        SDL_Surface* temp = IMG_Load(pelota);
        Texture = SDL_CreateTextureFromSurface(ren, temp);
        guisante.x = obj.peas[gus].x_location;
        guisante.y = obj.peas[gus].row;
        SDL_RenderCopy(ren, Texture, NULL, &guisante);
    }
}

//funcion para que la pea se mueva desde un punto hasta el zombie
void MoverPea(Objetos& obj) {
    for (int gus = 0; gus < obj.peas.size(); gus++) {
        obj.peas[gus].x_location += 5;
    }
}

//funcion para crear soles randomly
//cada sol cuesta 50
void Create_Suns(Objetos& obj) {
	srand(time(NULL));
	Sun temp;
	temp.MoveOnY = 5;
	temp.wait_seconds = 20;
	int row = 1 + (rand() % 5);
	switch (row) {
	case 1:
		temp.final_row = 84;
		break;
	case 2:
		temp.final_row = 178;
		break;
	case 3:
		temp.final_row = 278;
		break;
	case 4:
		temp.final_row = 381;
		break;
	case 5:
		temp.final_row = 473;
		break;
	}
	int col = 1 + (rand() % 9);
	switch (col) {
	case 1:
		temp.final_col= 933;
		break;
	case 2:
		temp.final_col = 861;
		break;
	case 3:
		temp.final_col = 781;
		break;
	case 4:
		temp.final_col = 703;
		break;
	case 5:
		temp.final_col = 619;
		break;
	case 6:
		temp.final_col = 541;
		break;
	case 7:
		temp.final_col = 460;
		break;
	case 8:
		temp.final_col = 382;
		break;
	case 9:
		temp.final_col = 301;
		break;

	}
	obj.suns.push_back(temp);
	cout << "\n nuevo sol Y:"<< temp.final_col<<"\n";
}

//funcion para crear zombies random
void RandZombies(Objetos &obj) {
    srand(time(NULL));
    Zombie temp;
    temp.x_location = 999;
    temp.health = 10;
    temp.moving = true;
    temp.directory = zombie;
    int row = 1 + (rand() % 5);
    temp.row = row;
        switch (row) {
            case 1:
                temp.y_location = 84;
                break;
            case 2:
                temp.y_location = 178;
                break;
            case 3:
                temp.y_location = 278;
                break;
            case 4:
                temp.y_location = 381;
                break;
            case 5:
                temp.y_location = 473;
                break;
        }
        cout << temp.y_location<< "\n";
        obj.zombies.push_back(temp);
    }
    

//funcion para mover el zombie desde derecha a izquierda
void move_zombies(vector<Zombie>& zombies) {
	for (int i = 0; i < zombies.size(); i++) {
		if (zombies[i].moving)
			zombies[i].x_location -= 2;
        if(zombies[i].x_location==0){
            zombies[i].health--;
        }
	}
}

//funcion para imprimir los peashooters
void PrintPeashooters(SDL_Renderer* ren, Objetos &obj) {
    for (int gus = 0; gus < obj.peashooter.size(); gus++) {
        SDL_Surface* temp = IMG_Load(pea);
        Texture = SDL_CreateTextureFromSurface(ren, temp);
        if (temp == NULL ) {
            cout << "Error loading image: " << SDL_GetBasePath();
            return;
        }
        Espacio.x = obj.peashooter[gus].col;
        Espacio.y = obj.peashooter[gus].row;
        SDL_RenderCopy(ren, Texture, &movePea, &Espacio);
    }
}

void mostrarWalnuts(SDL_Renderer* ren, Objetos &obj) {
    for (int gus = 0; gus < obj.walnut.size(); gus++) {
        SDL_Surface* temp = IMG_Load(walNut);
        Texture = SDL_CreateTextureFromSurface(ren, temp);
        if (temp == NULL ) {
            cout << "Error loading image: " << SDL_GetBasePath();
            return;
        }
        pos.x = obj.walnut[gus].col;
        pos.y = obj.walnut[gus].row;
        SDL_RenderCopy(ren, Texture, &moveWalnut, &pos);
    }
}
//funcion para imprimir los zombies
void MostrarZombies(SDL_Renderer* ren, vector<Zombie>& zombies, Objetos& obj, vector<vector< Block> > sc) {
    Zombie zomb;
	for (int i = 0; i < zombies.size(); i++) {
		
        //cambiar sprites dependiendo de la health
        if(zombies[i].health==10){
//                zombies[i].directory = zombie;
            SDL_Surface* temp = IMG_Load(zombie);
            Texture = SDL_CreateTextureFromSurface(ren, temp);
        }else if (zombies[i].health<9 && zombies[i].health>=4){
//                zombies[i].directory = danger1;
            SDL_Surface* temp = IMG_Load(danger1);
            Texture = SDL_CreateTextureFromSurface(ren, temp);
        }else if(zombies[i].health<4){
           // zombies[i].directory = danger1;
            SDL_Surface* temp = IMG_Load(danger1);
            Texture = SDL_CreateTextureFromSurface(ren, temp);
        }else if(ZombieChocadoConPlantas(obj, zomb, sc)){
           // zombies[i].directory = comiendo;
            SDL_Surface* temp = IMG_Load(comiendo);
            Texture = SDL_CreateTextureFromSurface(ren, temp);
        }

        space.x = zombies[i].x_location;
        space.y = zombies[i].y_location;
        if(space.x > 256){
            SDL_RenderCopy(ren, Texture, &zWalk, &space);
        }
        else {
            zombies.erase(zombies.begin()+i);
        }
	}
    
}

//funcion para que los soles cambien de posicion randomly
void MoverSoles(vector<Sun>& sol) {
	for (int i = 0; i < sol.size(); i++) {
		if (sol[i].MoveOnY < sol[i].final_row) {
			sol[i].MoveOnY += 5;
		}
		else if(sol[i].wait_seconds>0) {
			sol[i].wait_seconds--;
		}
		else {
			sol.erase(sol.begin() + i);
		}
	}
}

//funcion para imprimir soles
void MostrarSoles(SDL_Renderer* ren, vector<Sun>& sol) {
	for (int i = 0; i < sol.size(); i++) {
		SDL_Surface* temp = IMG_Load(sunny);
		Texture = SDL_CreateTextureFromSurface(ren, temp);
		cuadro.x = sol[i].final_col;
		cuadro.y = sol[i].MoveOnY;
			SDL_RenderCopy(ren, Texture, NULL, &cuadro);
	}
}

//funcion para quitarle vida a los zombies
void QuitarVidas(vector<Peashooter>& peas, vector<Zombie>& zomb){
    for (int i =0; i < zomb.size(); i++){
        if(zomb[i].x_location == peas[i].row){
            zomb[i].health--;
        }
    }
}

void sumarSoles(Objetos &obj, vector<vector<Block> >& sc, int mouse_x, int mouse_y, bool &sun_picked, Jugador &player){
    for(int i=0; i<obj.suns.size(); i++){
        int row = obj.suns[i].final_row;
        int col = obj.suns[i].final_col;
        int right = sc[row][col].x2;
        int left = sc[row][col].x1;
        if (mouse_x > left && mouse_x < right){
            obj.suns.erase(obj.suns.begin() + i);
            sun_picked = true;
            player.sol_total += 50;
            return;
        }
        sun_picked = false;
    }
}

//boolean para saber que icon fue seleccionado
bool iconSelected(Icons i,  int y){
    i.is_sunflower_chosen = false;
    i.is_peashooter_chosen = false;
    i.is_walnut_chosen = false;
    if((y>103) && (y<163)){
        i.is_sunflower_chosen= true;
    }else if((y>231) && (y<291)){
        i.is_walnut_chosen = true;
    }else{
        i.is_peashooter_chosen = true;
    }
    return false;
}

//boolean para crear plantas dependiendo del icon choosen
void crearPlantas(Objetos &obj, Icons & icon, Jugador &player, int x, int y){
    int row = y;
    int col = x;
    if(icon.is_peashooter_chosen && player.sol_total>=100){
        Peashooter ptemp;
        ptemp.row = row;
        ptemp.col = col;
        obj.peashooter.push_back(ptemp);
        player.sol_total -=100;
    }else if(icon.is_sunflower_chosen && player.sol_total>=50){
        Sunflower stemp;
        stemp.row = row;
        stemp.col = col;
        obj.sunflower.push_back(stemp);
        player.sol_total-=50;
    }else if(icon.is_walnut_chosen && player.sol_total>=50){
        Walnut wtemp;
        wtemp.row = row;
        wtemp.col = col;
        obj.walnut.push_back(wtemp);
        player.sol_total-=50;
    }
}


//funcion para display los icons de las plantas
void display_icon( SDL_Renderer* renderer){
    //crear las imagenes de los icons
    SDL_Surface* pDim = IMG_Load(dimIconP);
    SDL_Surface* p = IMG_Load(iconP);
    SDL_Surface* sDim = IMG_Load(dimIconS);
    SDL_Surface* s = IMG_Load(iconS);
    SDL_Surface* wDim = IMG_Load(dimIconW);
    SDL_Surface* w = IMG_Load(iconW);
    dimP = SDL_CreateTextureFromSurface(renderer, pDim);
    PeaIcon = SDL_CreateTextureFromSurface(renderer, p);
    dimS = SDL_CreateTextureFromSurface(renderer, sDim);
    SunIcon = SDL_CreateTextureFromSurface(renderer, s);
    dimW = SDL_CreateTextureFromSurface(renderer, wDim);
    WalIcon =SDL_CreateTextureFromSurface(renderer, w);
    int width =89, height = 60, iconX = 50, peaY = 167, walnutY = 231, sunY = 103;
 
    dibujoPea.x = iconX;
    dibujoPea.y = peaY;
    dibujoPea.w = width;
    dibujoPea.h = height;
    dibujoSun.x = iconX;
    dibujoSun.y = sunY;
    dibujoSun.w = width;
    dibujoSun.h = height;
    dibujoWalnut.x = iconX;
    dibujoWalnut.y = walnutY;
    dibujoWalnut.w = width;
    dibujoWalnut.h = height;
}


    /*
 ICON_BAR_X1 20
ICON_BAR_X2 113
 ICON_BAR_Y1 102
 ICON_BAR_Y2 292
 
  ICON_WIDTH 89
  ICON_HEIGHT 60
 
 #define SUNFLOWER_ICON_Y1 103
 #define PEASHOOTER_100_ICON_Y1 167
 #define WALNUT_ICON_Y1 231

 
 win.draw_png(SUN_DIRECTORY, 5, 5, SUN_WIDTH, SUN_HEIGHT);
     win.draw_png(SUN_COUNT_TEXT_FIELD_DIRECTORY, 85, 33, SUN_COUNT_WIDTH, SUN_COUNT_HEIGHT);
     win.show_text(to_string(player.sun_count), 100, 33);
 
 void determine_icon_chosen(Icons & icons, int mouse_y){
     icons.is_peashooter_chosen = false;
     icons.is_walnut_chosen = false;
     icons.is_sunflower_chosen = false;
     if (mouse_y > SUNFLOWER_ICON_Y1 && mouse_y < SUNFLOWER_ICON_Y1 + ICON_HEIGHT)
         icons.is_sunflower_chosen = true;
     else if (mouse_y > PEASHOOTER_100_ICON_Y1 &&
         mouse_y < PEASHOOTER_100_ICON_Y1 + ICON_HEIGHT)
         icons.is_peashooter_chosen = true;
     else
         icons.is_walnut_chosen = true;
 }
 
 */
//}



int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    vector<vector< Block> > sc;
    bool run = true;
    Jugador player;
    Objetos Object;
    Icons icon;
    cuadro.h = 44;
    cuadro.w = 44;
    space.h = 60;
    space.w = 60;
    pos.w = 58;
    pos.h = 60;
    Espacio.w = 58;
    Espacio.h = 60;
    guisante.w = 20;
    guisante.h = 20;
    cout << Object.zombies.size()<< "\n";
    
    SDL_Window* window = SDL_CreateWindow("YIPEEEEEE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1035, 600, SDL_WINDOW_SHOWN);
    if(window==NULL){
        cout<<"No carga ventana";
        return 4;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Renderer* ayuda = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface* temple = IMG_Load(patio);
    SDL_Surface *sun_icon = IMG_Load(sunny);
    
    //para chequear que pasaba con las imagenes
    if (temple == NULL || sun_icon == NULL ) {
        cout << "Error loading image: " << SDL_GetBasePath();
        return 5;
    }
    solContador = SDL_CreateTextureFromSurface(renderer, sun_icon);
    Fondo = SDL_CreateTextureFromSurface(renderer, temple);
    
    SDL_FreeSurface(temple);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_SetRenderDrawColor(ayuda, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderClear(ayuda);
    
    //=============================================================
    //VALERIA PROBANDO SPRITES
    const int moving = 60;
    int y=0, x=0;
    int timeZombie=0, timeWalnut =0, timePea =0, timeSunflower=0;
    int txtWidth=0, txtHeight=0;
    SDL_QueryTexture(Texture, NULL, NULL, &txtWidth, &txtHeight);
    
    zWalk.x = zWalk.y =0;
    movePea.x = movePea.y = 0;
    moveWalnut.x = moveWalnut.y = 0;
    moveWalnut.h =32;
    moveWalnut.w = 27;
    movePea.h = 31;
    movePea.w = 27;
    zWalk.h = 49;
    zWalk.w = 41;
    solPos.x = solPos.y = 5;
    solPos.h = solPos.w = 100;
    player.sol_total=50;
    int soles = 60;
    //===========================================================
    
    int gus = 0;
    crearPeashooters(Object);
    while (run) {
        SDL_RenderCopy(renderer, Fondo, NULL, NULL);
        SDL_RenderCopy(renderer, solContador, NULL, &solPos);
        display_icon(renderer);
        
        //verificacion de como aparecen los icons
        if(player.sol_total < 50){
            //display todo en dim
            SDL_RenderCopy(renderer, dimP, NULL, &dibujoPea);
            SDL_RenderCopy(renderer, dimS, NULL, &dibujoSun);
            SDL_RenderCopy(renderer, dimW, NULL, &dibujoWalnut);
        }else if (player.sol_total>=50){
            //display solo las plantas sunflower y roca
            SDL_RenderCopy(renderer, SunIcon, NULL, &dibujoSun);
            SDL_RenderCopy(renderer, WalIcon, NULL, &dibujoWalnut);
            if(player.sol_total>=100){
                //mostrar peashooter
                SDL_RenderCopy(renderer, PeaIcon, NULL, &dibujoPea);
            }else{
                //poner el peashooter en dim
                SDL_RenderCopy(renderer, dimP, NULL, &dibujoPea);
            }
        }
        
        //zombies
        if (gus % 1200==0) {
            RandZombies(Object);
        }
        
        move_zombies(Object.zombies);
        MostrarZombies(renderer, Object.zombies, Object, sc);
        PrintPeashooters(renderer, Object);
        mostrarWalnuts(renderer, Object);
        
        
        //esto crea los sprites
        //contador para frame del sprite actual
        timeZombie++;
        timePea++;
        timeWalnut++;
        timeSunflower++;
        
        if(moving/timeZombie == 4){
            //set el contador a 0
            timeZombie =0;
            zWalk.x += 41;
            if(zWalk.x >= 369){
                zWalk.x = 0;
                
            }
        }
        
        if(moving/timePea ==6){
            timePea =0;
            movePea.x +=27;
            if(movePea.x>=217){
                movePea.x =0;
            }
        }
        
        if(moving/timeWalnut ==3){
            timeWalnut =0;
            moveWalnut.x +=27;
            if(moveWalnut.x>=136){
                moveWalnut.x =0;
            }
        }
        
        if(moving/timeSunflower ==3){
            timeSunflower =0;
            moveSunflower.x +=29;
            if(moveSunflower.x>=237){
                moveSunflower.x =0;
            }
        }
        
        
        
        if (gus % 1200==0) {
            Create_Suns(Object);
            crearWalnuts(Object);
        }
        
        for (int P = 0; P < Object.zombies.size();P++) {
            for (int G = 0; G < Object.peashooter.size();G++) {
                if (IsZombieInPeashooterRow(Object.peashooter[G],Object.zombies[P]) && gus %250==0) {
                    crear_Pea(Object.peashooter[G].row, Object.peashooter[G].col, Object);
                }
            }
        }
        
        MoverPea(Object);
        mostrarPea(Object, renderer);
        
        for (int A = 0; A < Object.zombies.size(); A++) {
            for (int L = 0; L < Object.peas.size(); L++) {
                if (PeaGolpeadoZombie(Object.peas[L], Object.zombies[A]) && IsZombieInPeaRow(Object.peas[L], Object.zombies[A])){
                    apply_pea_hitting_zombie(Object, L, A);
                }
                else if (Object.peas[L].x_location == 1035) {
                    Object.peas.erase(Object.peas.begin() + L);
                }
            }
        }
        SDL_GetMouseState(&x, &y);
        cout<< x<< " : "<< y<<endl;
        bool solClick;
        
        sumarSoles(Object, sc, x, y, solClick, player);
        
        if(iconSelected(icon, y)){
            crearPlantas(Object, icon, player, x, y);
        }
        
        
        //soles
        MoverSoles(Object.suns);
        MostrarSoles(renderer, Object.suns);
        
        //fondo
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        gus+=10;
        SDL_Delay(30);
        SDL_Event event;
        SDL_PollEvent(&event);
        
        
        switch (event.type) {
            case SDL_QUIT:
                run = false;
                break;
                //            case SDL_MOUSEMOTION:
                //
                //
                //                    break;
            case SDL_MOUSEBUTTONDOWN:
                if(SDL_BUTTON_LEFT==event.button.button){
                    for(int i=0; i<Object.suns.size(); i++){
                        if(x == Object.suns[i].final_row){
                            player.sol_total+=50;
                            Object.suns.erase(Object.suns.begin() + y);
                        }
                        cout<<"SOLES: "<<player.sol_total;
                    }
                }
                break;
        }
        
        
        
        cout <<"Zombie Pos x: "<< gus << "\n Zombie Pos Y: " << space.y;
        
        cout << "\n\n"<< Object.zombies.size() << "\n";
        cout << Object.suns.size();
        return 0;
    }
}
