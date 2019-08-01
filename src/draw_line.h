#pragma once
#include <iostream>
#include <SDL.h>
int getheight(int numOfNodes) {
	int h = 0, subtrahend = 1;
	while (1) {
		numOfNodes -= subtrahend;
		if (numOfNodes <= 0) {
			return h;
		}
		++h;
		subtrahend *= 2;
	}
}

void drawline(SDL_Renderer* renderer, SDL_Point A, SDL_Point B) {
	SDL_RenderDrawLine(renderer, A.x, A.y, B.x, B.y);
	SDL_RenderPresent(renderer);
}
void drawLines(SDL_Renderer* renderer, std::vector<SDL_Point>& Points) {
	int lastParent = Points.size() / 2 - 1;

	for (int i = 0; i <= lastParent; ++i) {
		drawline(renderer, Points[i], Points[2 * i + 1]);
		if (i == lastParent && 2 * (i + 1) == Points.size())
			return;
		drawline(renderer, Points[i], Points[2 * (i+1)]);
	}
}
