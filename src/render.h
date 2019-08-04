#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "node.h"
#include <vector>
#include "draw_line.h"


void renderText(SDL_Renderer* renderer, std::string text, SDL_Color _color, SDL_Rect Message_rect,TTF_Font* font){

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), _color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface); //now you can convert it into a texture
	SDL_FreeSurface(textSurface);

	SDL_RenderCopy(renderer, textTexture, NULL, &Message_rect);
	SDL_DestroyTexture(textTexture);
}



void renderNodes(SDL_Renderer* renderer, std::vector<node> Nodes, TTF_Font* font, int numOfNodes) {
	for (int i = 0; i < numOfNodes; ++i){

		SDL_Surface *nodeSurface;
		SDL_Texture * nodeTexture;
		nodeSurface = SDL_LoadBMP("../res/black.bmp");
		if (!nodeSurface) {
			std::cout << SDL_GetError();
			return;
		}

		nodeTexture = SDL_CreateTextureFromSurface(renderer, nodeSurface);
		SDL_FreeSurface(nodeSurface);

		SDL_Rect rect = { Nodes[i].nodeCoord.x - 25, Nodes[i].nodeCoord.y-25 , 50, 50 };
		SDL_RenderCopy(renderer, nodeTexture, NULL, &rect);
		SDL_DestroyTexture(nodeTexture);
		
		
		std::string val = std::to_string(Nodes[i].value);
		SDL_Color white = { 255,255,255 };
		SDL_Rect textRect = { Nodes[i].nodeCoord.x - 18, Nodes[i].nodeCoord.y - 20, 30, 30 };
		
		renderText(renderer, val, white, textRect, font);
		
	}
}

void drawArrRects(SDL_Renderer* renderer, std::vector<node> Nodes, TTF_Font* font, int to, int from = 0 ) {
	SDL_Color black = { 0,0,0, };
	for (int i = from; i < to; ++i) {
		SDL_Rect arrTextRect = { Nodes[i].arrRect.x + 10, Nodes[i].arrRect.y + 10, 30, 30 };
		renderText(renderer, std::to_string(Nodes[i].value), black, arrTextRect, font);
		SDL_SetRenderDrawColor(renderer,0, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &Nodes[i].arrRect);
	}
}
void renderInputBox(SDL_Renderer* renderer, SDL_Rect rect) {
	SDL_Rect rect1;
	rect1.x = rect.x - 1; 
	rect1.y = rect.y - 1;
	rect1.w = rect.w + 2;
	rect1.h = rect.h + 2;
	SDL_RenderDrawRect(renderer, &rect1);
	SDL_SetRenderDrawColor(renderer, 255, 255 , 255, 255); // the rect color (solid red) 
	SDL_RenderFillRect(renderer, &rect);
}

void clearScreen(SDL_Renderer* renderer) {

	SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255);
	SDL_RenderClear(renderer);

}

void renderParticularNode(SDL_Renderer* renderer, node Node, TTF_Font* font, int x)
{
	SDL_Surface *nodeSurface;
	SDL_Texture * nodeTexture;
	if (x == 0)
		nodeSurface = SDL_LoadBMP("../res/green.bmp");
	else if (x == 1)
		nodeSurface = SDL_LoadBMP("../res/purple.bmp");
	else
		nodeSurface = SDL_LoadBMP("../res/red.bmp");
	if (!nodeSurface) {
		std::cout << SDL_GetError();
		return;
	}
	nodeTexture = SDL_CreateTextureFromSurface(renderer, nodeSurface);
	SDL_FreeSurface(nodeSurface);

	SDL_Rect rect = { Node.nodeCoord.x - 25, Node.nodeCoord.y - 25 , 50, 50 };
	SDL_RenderCopy(renderer, nodeTexture, NULL, &rect);
	SDL_DestroyTexture(nodeTexture);


	std::string val = std::to_string(Node.value);
	SDL_Color white = { 255,255,255 }, black = { 0,0,0 };
	SDL_Rect textRect = { Node.nodeCoord.x - 18, Node.nodeCoord.y - 20, 30, 30 };
	renderText(renderer, val, white, textRect, font);
}

