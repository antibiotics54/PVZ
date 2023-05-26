#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;
SDL_Texture* Texture, * Fondo;
SDL_Rect space, Image,cuadro;


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
		temp.directory = "foticos/Zombie.png";
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

void MostrarZombies(SDL_Renderer* ren,vector<Zombie>& zombies) {
	for (int i = 0; i < zombies.size(); i++) {
		SDL_Surface* temp = IMG_Load("foticos/Zombie.png");
		Texture = SDL_CreateTextureFromSurface(ren, temp);
		space.x = zombies[i].x_location;
		space.y = zombies[i].y_location;
		if (space.x > 256) {
			SDL_RenderCopy(ren, Texture, NULL, &space);
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
		SDL_Surface* temp = IMG_Load("foticos/Sun.png");
		Texture = SDL_CreateTextureFromSurface(ren, temp);
		cuadro.x = sol[i].final_col;
		cuadro.y = sol[i].MoveOnY;
			SDL_RenderCopy(ren, Texture, NULL, &cuadro);
	}
}
int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	bool run = true;
	Objetos Object;
	cuadro.h = 44;
	cuadro.w = 44;
	space.h = 100;
	space.w = 50;
	cout << Object.zombies.size()<< "\n";

	SDL_Window* window = SDL_CreateWindow("YIPEEEEEE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1035, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Surface* temple = IMG_Load("foticos/Patio.png");
	Fondo = SDL_CreateTextureFromSurface(renderer, temple);
	SDL_FreeSurface(temple);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	int gus = 0;
	while (run) {
		SDL_RenderCopy(renderer, Fondo, NULL, NULL);
		if (gus % 1200==0) {
			RandZombies(Object);
		}
        move_zombies(Object.zombies);
	    MostrarZombies(renderer, Object.zombies);
		if (gus % 1200==0) {
			Create_Suns(Object);
		}
		MoverSoles(Object.suns);
		MostrarSoles(renderer, Object.suns);
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
