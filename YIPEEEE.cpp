#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;
SDL_Texture* Texture, * Fondo;
SDL_Rect space, Image,cuadro,Espacio, guisante;

struct Block {
	int x1, x2;
	int y1, y2;
};

struct Icons {
	bool is_sunflower_chosen;
	bool is_peashooter_chosen;
	bool is_walnut_chosen;
	string sunflower_icon_directory;
	string peashooter_icon_directory;
	string walnut_icon_directory;
};


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
	vector<Pea> peas;
};


vector<vector<Block> > Screen;
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
void PrintPeashooters(SDL_Renderer* ren,Objetos &obj) {
	for (int gus = 0; gus < obj.peashooter.size(); gus++) {
		SDL_Surface* temp = IMG_Load("foticos/Peashooter.png");
		Texture = SDL_CreateTextureFromSurface(ren, temp);
		Espacio.x = obj.peashooter[gus].col;
		Espacio.y = obj.peashooter[gus].row;
		SDL_RenderCopy(ren, Texture, NULL, &Espacio);
	}
}

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

bool ZombiePuedeMoverse(Zombie zombie, int row, int col, vector<vector<Block> >& map) {
	int right_limit = map[row][col].x2 - 35;
	int left_limit = map[row][col].x1;
	int zombie_new_location = zombie.x_location - 1;
	if (zombie.row == row && zombie_new_location < right_limit && zombie_new_location > left_limit)
		return true;
	return false;
}

bool ZombieChocadoConPlantas(Objetos& elements, Zombie& zombie, vector<vector<Block> >& map) {
	for (int i = 0; i < elements.walnut.size(); i++) {
		if (ZombiePuedeMoverse(zombie, elements.walnut[i].row, elements.walnut[i].col, map)) {
			zombie.moving = false;
			return true;
		}
	}
	for (int i = 0; i < elements.peashooter.size(); i++) {
		if (ZombiePuedeMoverse(zombie, elements.peashooter[i].row, elements.peashooter[i].col, map)) {
			zombie.moving = false;
			return true;
		}
	}
	for (int i = 0; i < elements.sunflower.size(); i++) {
		if (ZombiePuedeMoverse(zombie, elements.sunflower[i].row, elements.sunflower[i].col, map)) {
			zombie.moving = false;
			return true;
		}
	}
	zombie.moving = true;
	return false;
}

bool IsZombieInPeashooterRow(Peashooter peashooter, Zombie zombie) {
	if (zombie.y_location == peashooter.row) {
		return true;
	}
	return false;
}


bool IsZombieInPeaRow(Pea pea, Zombie zombie) {
	if (zombie.y_location+5 == pea.row) {
		return true;
	}
	return false;
}

bool PeaGolpeadoZombie(Pea pea, Zombie zombie) {
	if (zombie.x_location <= pea.x_location)
		return true;
	return false;
}

void apply_pea_hitting_zombie(Objetos& elements, int p_ind, int z_ind) {
	if (PeaGolpeadoZombie(elements.peas[p_ind], elements.zombies[z_ind])) {
		elements.zombies[z_ind].health--;
		elements.peas.erase(elements.peas.begin() + p_ind);
		if (elements.zombies[z_ind].health == 0)
			elements.zombies.erase(elements.zombies.begin() + z_ind);
	}
}
void crear_Pea(int col,int row, Objetos& obj) {
	Pea temp;
	temp.row = col+5;
	temp.x_location = row+35;
	obj.peas.push_back(temp);
}
void mostrarPea(Objetos& obj, SDL_Renderer* ren) {
	for (int gus = 0; gus < obj.peas.size(); gus++) {
		SDL_Surface* temp = IMG_Load("foticos/Pea.png");
		Texture = SDL_CreateTextureFromSurface(ren, temp);
		guisante.x = obj.peas[gus].x_location;
		guisante.y = obj.peas[gus].row;
		SDL_RenderCopy(ren, Texture, NULL, &guisante);
	}
}

void MoverPea(Objetos& obj) {
	for (int gus = 0; gus < obj.peas.size(); gus++) {
		obj.peas[gus].x_location += 5;
	}
}

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
	std::cout << "\n nuevo sol Y:"<< temp.final_col<<"\n";
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
		std::cout << temp.y_location<< "\n";
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
	Espacio.w = 58;
	Espacio.h = 60;
	cuadro.h = 44;
	cuadro.w = 44;
	space.h = 100;
	space.w = 50;
	guisante.w = 20;
	guisante.h = 20;
	std::cout << Object.zombies.size()<< "\n";

	SDL_Window* window = SDL_CreateWindow("YIPEEEEEE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1035, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Surface* temple = IMG_Load("foticos/Patio.png");
	Fondo = SDL_CreateTextureFromSurface(renderer, temple);
	SDL_FreeSurface(temple);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	int gus = 0;
	crearPeashooters(Object);
	while (run) {
		SDL_RenderCopy(renderer, Fondo, NULL, NULL);
		PrintPeashooters(renderer, Object);
		if (gus % 1200==0) {
			RandZombies(Object);
		}
        move_zombies(Object.zombies);
	    MostrarZombies(renderer, Object.zombies);
		if (gus % 1200==0) {
			Create_Suns(Object);
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
	std::cout <<"Zombie Pos x: "<< gus << "\n Zombie Pos Y: " << space.y;

	std::cout << "\n\n"<< Object.zombies.size() << "\n";
  std::cout << Object.suns.size()<<"\n";
  std::cout << "Fila: " << Object.peas[0].row << "\n X: " << Object.peas[0].x_location;
	return 0;
}
