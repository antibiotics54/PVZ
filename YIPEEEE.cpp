#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;
SDL_Texture* Texture, * Fondo;
SDL_Rect space, Image;


struct Sun {
	int final_col;
	int final_row;
	int y_location;
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

struct Zombie {
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
};

void RandZombies(int counter, Objetos &obj) {
	if(counter % 12000)
		srand(time(NULL));
		Zombie temp;
		temp.x_location = 999;
		temp.health = 10;
		temp.moving = true;
		temp.directory = "foticos/Zombie.png";
		int row = 1 + (rand() % 5);
		switch (row) {
		case 1:
			temp.y_location = 184;
			break;
		case 2:
			temp.y_location = 276;
			break;
		case 3:
			temp.y_location = 378;
			break;
		case 4:
			temp.y_location = 465;
			break;
		case 5:
			temp.y_location = 563;
			break;
		}
		cout << temp.y_location;
		obj.zombies.push_back(temp);
	}

void move_zombies(vector<Zombie>& zombies) {
	for (int i = 0; i < zombies.size()-1; i++) {
		if (zombies[1].moving)
			zombies[i].x_location -= 2;
	}
}

void MostrarPantalla(SDL_Renderer* ren,vector<Zombie>& zombies) {
	for (int i = 0; i < zombies.size()-1; i++) {
		SDL_Surface* temp = IMG_Load("foticos/Zombie.png");
		Texture = SDL_CreateTextureFromSurface(ren, temp);
		space.x = zombies[i].x_location;
		space.y = zombies[i].y_location;
		if (space.x > 256) {
			SDL_RenderCopy(ren, Texture, NULL, &space);
		}
		
	}
}

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	bool run = true;
	Objetos Object;
	space.h = 100;
	space.w = 50;
	cout << Object.zombies.size();

	SDL_Window* window = SDL_CreateWindow("YIPEEEEEE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1035, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Surface* temp = IMG_Load("foticos/Zombie.png");
	Texture = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_Surface* temple = IMG_Load("foticos/Patio.png");
	Fondo = SDL_CreateTextureFromSurface(renderer, temple);
	Texture = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);
	SDL_FreeSurface(temple);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	int gus = 0;
	space.y = 180;
	int move=999;
	while (run) {
		space.x=move;
		SDL_RenderCopy(renderer, Fondo, NULL, NULL);
		//RandZombies(gus, Object);
	    //move_zombies(Object.zombies);
		//MostrarPantalla(renderer, Object.zombies);
		
		 	if (move > 256) {
			SDL_RenderCopy(renderer, Texture, NULL, &space);

		}
		
		
		
			SDL_RenderPresent(renderer);
			
			gus++;
			move--;
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
	return 0;
}
