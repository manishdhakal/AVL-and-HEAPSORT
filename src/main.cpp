
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "text_render.h"
#include <vector>
#include <cmath>
#include "draw_line.h"

#define W 1536
#define H 864
//#define W SCREEN_WIDTH 
//#define H SCREEN_HEIGHT


void addPoint(std::vector<SDL_Point>& Points) {
	int treeHeight = getheight(Points.size()+1);
	int newIndex = Points.size(), parIndex;

	SDL_Point New;
	New.y = 100 *( treeHeight +1);
	if (newIndex % 2 == 0){
		parIndex = newIndex / 2 -1;
		New.x = Points[parIndex].x + W / (int)pow(2, treeHeight + 1);
		
	}
	else{
		parIndex = newIndex / 2;
		New.x = Points[parIndex].x - W / (int)pow(2, treeHeight + 1);
		
	}
	Points.push_back(New);
}


int main(int argc, char *argv[]) {

	SDL_Window *window; 
	SDL_DisplayMode DM;
	std::vector<SDL_Point> Points(1);
	Points[0].x = W / 2;
	Points[0].y = 100;
	addPoint(Points);

	bool quit = false;
	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

	SDL_GetCurrentDisplayMode(0, &DM);
	const int SCREEN_WIDTH = DM.w;
	const int SCREEN_HEIGHT = DM.h;
	
	std::cout << W << "  " << H <<'\n' ;
	TTF_Init();


	window = SDL_CreateWindow(
		"DSA",                 
		SDL_WINDOWPOS_UNDEFINED,           
		SDL_WINDOWPOS_UNDEFINED,          
		SCREEN_WIDTH,                               // width, in pixels
		SCREEN_HEIGHT-60,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);

	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Renderer* renderer;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_Surface *screenSurface, *nodeSurface;

	nodeSurface = SDL_LoadBMP("../res/black.bmp");
	if (!nodeSurface) {
		std::cout << SDL_GetError();
		return 1;
	}

	screenSurface = SDL_GetWindowSurface(window);
	SDL_BlitSurface(nodeSurface, NULL, screenSurface, NULL);
	
	TTF_Font* arial = TTF_OpenFont("../res/arial.ttf", 200);

	if (!arial) {
		std::cout << TTF_GetError() << std::endl;
		return 1;
	}
	
	SDL_Event evnt;
	while (!quit) {
		
		
		SDL_Color _color = {255,255,255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

		SDL_Rect Message_rect; //create a rect
		Message_rect.x = 100; //controls the rect's x coordinate 
		Message_rect.y = 100; // controls the rect's y coordinte
		Message_rect.w = 100; // controls the width of the rect
		Message_rect.h = 100; // controls the height of the rect


		renderText(renderer, "mansih", _color, Message_rect, arial);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		drawLines(renderer, Points);

		while (SDL_PollEvent(&evnt)) {
			
			switch (evnt.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				if (evnt.key.keysym.sym == SDLK_SPACE) {
					addPoint(Points);
					SDL_UpdateWindowSurface(window);
					break;
				}
			}
			break;
		}
	}

	TTF_CloseFont(arial);
	TTF_Quit();
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
