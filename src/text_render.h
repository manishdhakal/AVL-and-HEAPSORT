#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

void renderText(SDL_Renderer* renderer, std::string text, SDL_Color _color, SDL_Rect Message_rect, TTF_Font* font){

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), _color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture
	SDL_FreeSurface(surfaceMessage);

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	SDL_RenderPresent(renderer);
}

