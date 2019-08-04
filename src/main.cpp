
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

bool clickedBox(SDL_Point p, SDL_Rect rect) {
	return (p.x > rect.x && p.x < rect.x + rect.w && p.y > rect.y && p.y < rect.y + rect.h);
}

void getInput(SDL_Renderer* renderer ,std::string& inputText, bool& isQuit, SDL_Rect inputBoxRect, SDL_Rect buttonRect) {
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
				if ((evnt.key.keysym.sym == SDLK_RETURN || evnt.key.keysym.sym == SDLK_KP_ENTER) && inputText != "" ) {
					std::cout << "pressed enter" << std::endl;
					return ;
				}
				else if(evnt.key.keysym.sym == SDLK_BACKSPACE && inputText.size() > 0 )
				{
					inputText.pop_back();
					renderInputBox(renderer, inputBoxRect);
					std::cout << inputText << std::endl;
				}
			}
			else if (evnt.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				x = evnt.button.x;
				y = evnt.button.y;
				if (clickedBox({ x,y }, buttonRect ) && inputText != "")
					return;

			}

			if (evnt.type == SDL_TEXTINPUT) {
				int ascii =  int(evnt.text.text[0]);
				if( ascii > 47 && ascii < 58 && inputText.size() < 3)
					inputText += evnt.text.text;
				std::cout << inputText << std::endl;
			}
		}
		SDL_Color black = { 0,0,0 };
		SDL_Rect textRect = { inputBoxRect.x+3, inputBoxRect.y+3, (int)(inputText.size()) * 25, 25 };
		
		renderText(renderer, inputText, black, textRect, arial);

		for(int i = 0; i < inputText.size(); ++i) { 
			drawLine(renderer, { inputBoxRect.x + 3 + i * 25 , inputBoxRect.y+3 }, { inputBoxRect.x + 3 + i * 25 , inputBoxRect.y+27 }, {255,255,255});
		}
		if (duration <= 300) {
			
			drawLine(renderer, { inputBoxRect.x + 3 + (int)(inputText.size()) * 25 , inputBoxRect.y + 3 }, { inputBoxRect.x + 3 + (int)(inputText.size()) * 25 , inputBoxRect.y + 27 });
		}
		else if (duration < 600 && duration > 300) {
			drawLine(renderer, { inputBoxRect.x + 3 + (int)(inputText.size()) * 25 , inputBoxRect.y + 3 }, { inputBoxRect.x + 3 + (int)(inputText.size()) * 25 , inputBoxRect.y + 27 }, { 255,255,255 });

		}
		else
			start = std::clock();
		SDL_RenderPresent(renderer);
		
	}
	TTF_CloseFont(arial);
}

void heapSort(std::vector<node>& Nodes,SDL_Renderer* renderer, TTF_Font* font)
{
	//std::vector<node> temp;
	int n, elt, son, parent, ivalue;
	n = Nodes.size();

	drawLines(renderer, Nodes, Nodes.size());
	renderNodes(renderer, Nodes, font, Nodes.size());

	for (int i = 1; i < n; i++)
	{
		elt = Nodes[i].value;
		son = i;
		parent = (son - 1) / 2;
		while (son > 0 && Nodes[parent].value < elt)
		{
			renderParticularNode(renderer, Nodes[son], font, 1);
			renderParticularNode(renderer, Nodes[parent], font, 1);
			SDL_RenderPresent(renderer);
			SDL_Delay(2000);
			Nodes[son].value = Nodes[parent].value;
			son = parent;
			parent = (son - 1) / 2;
			
		}
		Nodes[son].value = elt;
		clearScreen(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		drawLines(renderer, Nodes, Nodes.size());
		renderNodes(renderer, Nodes, font, Nodes.size());
		SDL_RenderPresent(renderer);
		SDL_Delay(2000);

	}
	//take out max
	for (int i = n - 1; i > 0; i--)
	{
		renderParticularNode(renderer, Nodes[0], font, 0);
		SDL_Delay(2000);

		ivalue = Nodes[i].value;
		Nodes[i].value = Nodes[0].value;
		parent = 0;
		if (i == 1)
			son = -1;
		else
			son = 1;
		if (i > 2 && Nodes[2].value > Nodes[1].value)
			son = 2;
		while (son >= 0 && ivalue < Nodes[son].value)
		{
			renderParticularNode(renderer, Nodes[son], font, 1);
			SDL_RenderPresent(renderer);
			SDL_Delay(2000);

			Nodes[parent].value = Nodes[son].value;
			parent = son;
			son = 2 * parent + 1;
			if (son + 1 <= i - 1 && Nodes[son].value < Nodes[son + 1].value)
				son++;
			if (son > i - 1)
				son = -1;
		}
		
		Nodes[parent].value = ivalue;
		clearScreen(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		
		drawLines(renderer, Nodes, i);
		renderNodes(renderer, Nodes, font, i);
		drawArrRects(renderer, Nodes, font, n, i);
		SDL_RenderPresent(renderer);
		SDL_Delay(2000);
	}
	clearScreen(renderer);
	drawArrRects(renderer, Nodes, font, n);
}

int main(int argc, char *argv[]) {

	SDL_Window *window;
	SDL_Renderer* renderer;
	SDL_DisplayMode DM;
	SDL_Color textColor = {0,0,0};
	std::string inputText = "";

	bool isQuit = false, gotNumData = false, allDataGiven = false,isHeapSorted = false;
	int numData;
	std::string numData_str;

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
		W,									// width, in pixels
		H-60,                               // height, in pixels
		SDL_WINDOW_OPENGL                   // flags - see below
	);

	if (window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}
	
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255);

	SDL_RenderClear(renderer);

	TTF_Font* aller = TTF_OpenFont("../res/aller.ttf",500);
	TTF_Font* arial = TTF_OpenFont("../res/arial.ttf", 500);
	if (!aller) {
		std::cout << TTF_GetError() << std::endl;
		return 1;
	}

	SDL_Rect textInputRect, buttonRect, patchRect;
	textInputRect.x = 50;
	textInputRect.y = 100;
	textInputRect.w = 100;
	textInputRect.h = 32;

	buttonRect = { 200,100,150,32 };
	patchRect = { 45, 95, 500,40 };
	int count = 0;

	SDL_Event evnt;
	while (!isQuit) {
		if (!allDataGiven) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawRect(renderer, &buttonRect);

			SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderFillRect(renderer, &buttonRect);

			

			if (!gotNumData) {
				renderText(renderer, "OK", { 0,0,0 }, { buttonRect.x + 5 , buttonRect.y + 5, buttonRect.w - 50, buttonRect.h - 10 }, arial);
			}
			else
			{
				renderText(renderer, "Next", { 0,0,0 }, { buttonRect.x + 5 , buttonRect.y + 5, buttonRect.w - 15, buttonRect.h - 10 }, arial);
			}

			renderInputBox(renderer, textInputRect);
			if (gotNumData) {
				if (count < numData) {
					getInput(renderer, inputText, isQuit, textInputRect, buttonRect);
					if (inputText != "")
					{
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
							addNode(Nodes, std::stoi(inputText), W, H);
						++count;
					}
				}
				else
					allDataGiven = true;
			}
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			drawLines(renderer, Nodes, Nodes.size());

			renderNodes(renderer, Nodes, aller, Nodes.size());
			drawArrRects(renderer, Nodes, arial, Nodes.size());

		}
		else {
			SDL_SetRenderDrawColor(renderer, 169, 169, 169, SDL_ALPHA_OPAQUE);
			SDL_RenderFillRect(renderer, &patchRect);
		}

		
		while (SDL_PollEvent(&evnt)) {
			
			switch (evnt.type) {
			
			case SDL_QUIT: {
				isQuit = true;
			}break;

			case SDL_MOUSEBUTTONDOWN: {
				if (!allDataGiven) {
					int x = evnt.button.x;
					int y = evnt.button.y;
					if (clickedBox({ x,y }, textInputRect)) {
						if (!gotNumData) {
							getInput(renderer, numData_str, isQuit, textInputRect, buttonRect);
							if (numData_str != "")
								numData = std::stoi(numData_str);
							gotNumData = true;
						}

					}
				}
			}break;
			}
		}
		if (allDataGiven && !isHeapSorted) {
			SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255);
			SDL_RenderClear(renderer);
			heapSort(Nodes, renderer, aller);
			isHeapSorted = true;

		}
		SDL_RenderPresent(renderer);

	}
	
	TTF_CloseFont(aller);
	TTF_CloseFont(arial);

	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
