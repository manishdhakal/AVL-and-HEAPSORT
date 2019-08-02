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

void renderNodes(SDL_Renderer* renderer, const std::vector<node> Nodes, TTF_Font* font) {
	for (int i = 0; i < Nodes.size(); ++i){

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
		
		
		std::string val = std::to_string(i);
		SDL_Color white = { 255,255,255 }, black = {0,0,0};
		SDL_Rect textRect = { Nodes[i].nodeCoord.x - 18, Nodes[i].nodeCoord.y - 20, 30, 30 };
		SDL_Rect arrTextRect = { Nodes[i].arrRect.x + 10, Nodes[i].arrRect.y + 10, 30, 30 };
		renderText(renderer, val, white, textRect, font);
		renderText(renderer, val, black, arrTextRect, font);
		drawRect(renderer, Nodes[i].arrRect);
		
	}
}

