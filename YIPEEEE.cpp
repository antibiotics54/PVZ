#include <SDL.h>
#include <iostream>
#include <SDL_image.h>

using namespace std;
SDL_Texture* Texture, *Fondo;
SDL_Rect space, Image;

void GameMechanics() {
	//Para
}
void Frames() {

}
int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	bool run = true;
	space.h = 100;
	space.w = 50;
	

	SDL_Window* window = SDL_CreateWindow("YIPEEEEEE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);
	SDL_Surface* temp = IMG_Load("foticos/ZombieWalkingSprites1.png");
	SDL_Surface* temple = IMG_Load("foticos/Patio.png");
	Fondo = SDL_CreateTextureFromSurface(renderer,temple);
	Texture = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);
	SDL_FreeSurface(temple);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	int gus = 700;
	space.y = 85;
	int speed = 100;
	int numFrames = 0;
	Image.x = 0;
	Image.h = 49;
	Image.w = 37;
	while (run) {
		space.x = gus;
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, Fondo, NULL, NULL);
		if (gus > 159) {
			Image.x = Image.x+(Image.w*numFrames);
	    SDL_RenderCopy(renderer, Texture, &Image, &space);
		SDL_RenderPresent(renderer);
		numFrames++;
		if (numFrames > 9) {
			numFrames = 0;
		}
		//gus--;
		}
		std::cout << "hello\n";
		SDL_Delay(250);
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
	//cout <<"Pos x: "<< gus << "Pos Y: " << space.y;
	return 0;
}