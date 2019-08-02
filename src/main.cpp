
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "render.h"
#include <vector>
#include <cmath>
#include "draw_line.h"
#include "node.h"


int main(int argc, char *argv[]) {

	
	SDL_Window *window;
	SDL_Renderer* renderer;
	SDL_DisplayMode DM;
	
	bool quit = false;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_GetCurrentDisplayMode(0, &DM);
	const int W = DM.w;
	const int H = DM.h;

	std::vector<node> Nodes;
	std::cout << Nodes.size() << std::endl;
	
	TTF_Init();

	window = SDL_CreateWindow(
		"DSA",                 
		SDL_WINDOWPOS_UNDEFINED,           
		SDL_WINDOWPOS_UNDEFINED,          
		W,                               // width, in pixels
		H-60,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);

	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}
	
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255);

	SDL_RenderClear(renderer);

	TTF_Font* arial = TTF_OpenFont("../res/aller.ttf",500);

	if (!arial) {
		std::cout << TTF_GetError() << std::endl;
		return 1;
	}


	SDL_Event evnt;
	while (!quit) {
		
		SDL_SetRenderDrawColor(renderer, 0,0,0, SDL_ALPHA_OPAQUE);
		drawLines(renderer, Nodes);

		renderNodes(renderer, Nodes, arial);

		while (SDL_PollEvent(&evnt)) {
			
			switch (evnt.type) {
			case SDL_QUIT:
				quit = true;
				
			case SDL_KEYDOWN:
				if (evnt.key.keysym.sym == SDLK_SPACE) {
					if (Nodes.size() == 0) {
						node New;
						New.nodeCoord.x = W / 2;
						New.nodeCoord.y = 400;
						New.arrRect.x = 50;
						New.arrRect.y = 50;
						New.arrRect.h = 50;
						New.arrRect.w = 50;
						Nodes.push_back(New);
					}
					else
						addNode(Nodes, W, H);	

				}
			}
		}
		SDL_RenderPresent(renderer);
	}

	TTF_CloseFont(arial);
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
