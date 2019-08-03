
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <cmath>
#include <string>
#include <ctime>

#include "render.h"
#include "draw_line.h"
#include "node.h"


void getInput(SDL_Renderer* renderer ,std::string& inputText, bool& isQuit, SDL_Rect rect) {
	inputText = "";
	SDL_Event evnt;
	TTF_Font* arial = TTF_OpenFont("../res/arial.ttf", 3000);
	auto start = std::clock();
	while (true) {

		float duration = float(std::clock() - start);
		//std::cout << duration << '\n';
		if(SDL_PollEvent(&evnt)){
			if(evnt.type == SDL_QUIT){
				isQuit = true;
				return ;
			}
			if (evnt.type == SDL_KEYDOWN) {
				if (evnt.key.keysym.sym == SDLK_RETURN || evnt.key.keysym.sym == SDLK_KP_ENTER) {
					std::cout << "pressed enter" << std::endl;
					return ;
				}
				else if(evnt.key.keysym.sym == SDLK_BACKSPACE && inputText.size() > 0 )
				{
					inputText.pop_back();
					renderInputBox(renderer, rect);
					std::cout << inputText << std::endl;
				}
			}

			if (evnt.type == SDL_TEXTINPUT) {
				int ascii =  int(evnt.text.text[0]);
				if( ascii > 47 && ascii < 58)
					inputText += evnt.text.text;
				std::cout << inputText << std::endl;
			}
		}
		SDL_Color black = { 0,0,0 };
		SDL_Rect textRect = { rect.x+3, rect.y+3, (int)(inputText.size()) * 25, 25 };
		
		renderText(renderer, inputText, black, textRect, arial);
		for(int i = 0; i < inputText.size(); ++i) { 
			drawLine(renderer, { rect.x + 3 + i * 25 , rect.y+3 }, { rect.x + 3 + i * 25 , rect.y+27 }, {255,255,255});
		}
		if (duration <= 300) {
			
			drawLine(renderer, { rect.x + 3 + (int)(inputText.size()) * 25 , rect.y + 3 }, { rect.x + 3 + (int)(inputText.size()) * 25 , rect.y + 27 });
		}
		else if (duration < 600 && duration > 300) {
			drawLine(renderer, { rect.x + 3 + (int)(inputText.size()) * 25 , rect.y + 3 }, { rect.x + 3 + (int)(inputText.size()) * 25 , rect.y + 27 }, { 255,255,255 });

		}
		else
			start = std::clock();
		SDL_RenderPresent(renderer);
		
	}
	TTF_CloseFont(arial);
}

bool clickedBox(SDL_Point p, SDL_Rect rect) {
	return (p.x > rect.x && p.x < rect.x + rect.w && p.y > rect.y && p.y < rect.y + rect.h);
}

int main(int argc, char *argv[]) {

	
	SDL_Window *window;
	SDL_Renderer* renderer;
	SDL_DisplayMode DM;
	SDL_Color textColor = {0,0,0};
	std::string inputText = "";

	bool isQuit = false;
	//int numData;

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

	SDL_Rect rect1;
	rect1.x = 50;
	rect1.y = 50;
	rect1.w = 200;
	rect1.h = 32;

	

	SDL_Event evnt;
	while (!isQuit) {
		renderInputBox(renderer, rect1);
		
		SDL_SetRenderDrawColor(renderer, 0,0,0, SDL_ALPHA_OPAQUE);
		drawLines(renderer, Nodes);

		renderNodes(renderer, Nodes, arial);

		while (SDL_PollEvent(&evnt)) {
			
			switch (evnt.type) {
			
			case SDL_QUIT: {
				isQuit = true;
			}break;

			case SDL_MOUSEBUTTONDOWN: {
				int x = evnt.button.x;
				int y = evnt.button.y;
				if (clickedBox({x,y}, rect1)) {
					getInput(renderer, inputText, isQuit, rect1);
					if (Nodes.size() == 0) {
						node New;
						New.nodeCoord.x = W / 2;
						New.nodeCoord.y = 400;
						New.arrRect.x = W / 2;
						New.arrRect.y = 50;
						New.arrRect.h = 50;
						New.arrRect.w = 50;
						New.value = std::stoi(inputText);
						Nodes.push_back(New);
					}
					else
						addNode(Nodes,std::stoi(inputText), W, H);
					
				}
			}break;
			}
		}
		SDL_RenderDrawRect(renderer, &rect1);
		SDL_RenderPresent(renderer);
	}


	
	TTF_CloseFont(arial);
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
