
#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <ctime>
#include <vector>
#include <SDL2_image/SDL_image.h>

using namespace std;
SDL_Texture* Texture, * Fondo, *solContador;
SDL_Rect space, Image,cuadro, zWalk;
int walkWidth, txtWidth;

//defini aqui arriba mis dirrectorios porque en mac es distinto
#define zombie "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/ZombieWalkingSprites1.png"
#define sunny "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/sun.png"
#define patio "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/Patio.png"
#define flor "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/sunflower.png"
#define pea "/Users/valeriaalfaro/Library/Developer/Xcode/DerivedData/PlantsZombies-fiokuwxnbevesecggirpjmijaqec/Build/Products/assets/png/peashooters.png"


struct Sun {
	int final_col;
	int final_row;
	int MoveOnY;
	int wait_seconds;
};

struct Sunflower {
	int row, col;
	int byte;
};

struct Walnut {
	int row, col;
	int byte;
	string directory;
};

struct Peashooter {
	int row, col;
	int byte;
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
};


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
    


void move_zombies(vector<Zombie>& zombies) {
	for (int i = 0; i < zombies.size(); i++) {
		if (zombies[i].moving)
			zombies[i].x_location -= 2;
	}
}

void MostrarZombies(SDL_Renderer* ren, vector<Zombie>& zombies) {
    
	for (int i = 0; i < zombies.size(); i++) {
		SDL_Surface* temp = IMG_Load(zombie);
		Texture = SDL_CreateTextureFromSurface(ren, temp);
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

void MostrarSoles(SDL_Renderer* ren, vector<Sun>& sol) {
	for (int i = 0; i < sol.size(); i++) {
		SDL_Surface* temp = IMG_Load(sunny);
		Texture = SDL_CreateTextureFromSurface(ren, temp);
		cuadro.x = sol[i].final_col;
		cuadro.y = sol[i].MoveOnY;
			SDL_RenderCopy(ren, Texture, NULL, &cuadro);
	}
}

void QuitarVidas(vector<Peashooter>& peas, vector<Zombie>& zomb){
    for (int i =0; i < zomb.size(); i++){
        if(zomb[i].x_location == peas[i].row){
            zomb[i].health--;
        }
    }
}

//void display_icons_in_icon_bar(Icons icons, Player player, window & win){
//    if (player.sun_count < 50){
//        win.draw_png(SUNFLOWER_ICON_DIM_DIRECTORY, ICON_BAR_X1 + 3, SUNFLOWER_ICON_Y1, ICON_WIDTH, ICON_HEIGHT);
//        win.draw_png(PEASHOOTER_100_ICON_DIM_DIRECTORY, ICON_BAR_X1 + 3, PEASHOOTER_100_ICON_Y1, ICON_WIDTH, ICON_HEIGHT);
//        win.draw_png(WALNUT_ICON_DIM_DIRECTORY, ICON_BAR_X1 + 3, WALNUT_ICON_Y1, ICON_WIDTH, ICON_HEIGHT);
//    }
//    else if (player.sun_count >= 50){
//        win.draw_png(SUNFLOWER_ICON_BRIGHT_DIRECTORY, ICON_BAR_X1 + 3, SUNFLOWER_ICON_Y1, ICON_WIDTH, ICON_HEIGHT);
//        win.draw_png(WALNUT_ICON_BRIGHT_DIRECTORY, ICON_BAR_X1 + 3, WALNUT_ICON_Y1, ICON_WIDTH, ICON_HEIGHT);
//        if (player.sun_count >= 100)
//            win.draw_png(PEASHOOTER_100_ICON_BRIGHT_DIRECTORY, ICON_BAR_X1 + 3, PEASHOOTER_100_ICON_Y1, ICON_WIDTH, ICON_HEIGHT);
//        else
//            win.draw_png(PEASHOOTER_100_ICON_DIM_DIRECTORY, ICON_BAR_X1 + 3, PEASHOOTER_100_ICON_Y1, ICON_WIDTH, ICON_HEIGHT);
//    }
//    return;

/*
 ICON_BAR_X1 20
ICON_BAR_X2 113
 ICON_BAR_Y1 102
 ICON_BAR_Y2 292
 
 ICON_BAR_WIDTH 95
  ICON_BAR_HEIGHT 194
  ICON_WIDTH 89
  ICON_HEIGHT 60
 
 win.draw_png(SUN_DIRECTORY, 5, 5, SUN_WIDTH, SUN_HEIGHT);
     win.draw_png(SUN_COUNT_TEXT_FIELD_DIRECTORY, 85, 33, SUN_COUNT_WIDTH, SUN_COUNT_HEIGHT);
     win.show_text(to_string(player.sun_count), 100, 33);
 
 */
//}



int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    bool run = true;
	Objetos Object;
	cuadro.h = 44;
	cuadro.w = 44;
	space.h = 60;
	space.w = 60;
	cout << Object.zombies.size()<< "\n";

	SDL_Window* window = SDL_CreateWindow("YIPEEEEEE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1035, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
//    SDL_Renderer* sprite = SDL_CreateRenderer(window, -1, 0);
	SDL_Surface* temple = IMG_Load(patio);
    SDL_Surface *sun_icon = IMG_Load(sunny);
    
    //para chequear que pasaba con las imagenes
    if (temple == NULL || sun_icon == NULL) {
        cout << "Error loading image: " << SDL_GetBasePath();
        return 5;
    }
    solContador = SDL_CreateTextureFromSurface(renderer, sun_icon);
    Fondo = SDL_CreateTextureFromSurface(renderer, temple);
    
    SDL_FreeSurface(temple);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    
    //=============================================================
    //VALERIA PROBANDO SPRITES
    const int moving = 60;
    int frameTime = 0, tiempo;
    int txtWidth=0, txtHeight=0;
    SDL_QueryTexture(Texture, NULL, NULL, &txtWidth, &txtHeight);

    zWalk.x = zWalk.y =0;
    zWalk.h = 49;
    zWalk.w = 41;
    
    //===========================================================

	
	int gus = 0;
	while (run) {
		SDL_RenderCopy(renderer, Fondo, NULL, NULL);
        
        //zombies
		if (gus % 1200==0) {
			RandZombies(Object);
		}
        
        move_zombies(Object.zombies);
        MostrarZombies(renderer, Object.zombies);
        
        
        //esto crea los sprites
        //contador para frame del sprite actual
        frameTime++;
        if(moving/frameTime == 2){
            //set el contador a 0
            frameTime =0;
            zWalk.x += 41;
            if(zWalk.x >= 369){
                zWalk.x = 0;
            }
        }
        
        
      
		if (gus % 1200==0) {
			Create_Suns(Object);
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
		default:
			break;
		}

	}
  cout <<"Zombie Pos x: "<< gus << "\n Zombie Pos Y: " << space.y;

  cout << "\n\n"<< Object.zombies.size() << "\n";
  cout << Object.suns.size();
	return 0;
}
