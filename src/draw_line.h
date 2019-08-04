#pragma once
#include <iostream>
#include <SDL.h>
#include "node.h"

void drawLine(SDL_Renderer* renderer, SDL_Point A, SDL_Point B, SDL_Color color = {0,0,0}) {
	SDL_SetRenderDrawColor(renderer, color.r , color.g, color.b, 255);
	SDL_RenderDrawLine(renderer, A.x, A.y, B.x, B.y);
}
void drawLines(SDL_Renderer* renderer, const std::vector<node>& Nodes, int numOfPoints) {
	int lastParent = numOfPoints / 2 - 1;

	for (int i = 0; i <= lastParent; ++i) {
		drawLine(renderer, Nodes[i].nodeCoord, Nodes[2 * i + 1].nodeCoord);
		if (i == lastParent && 2 * (i + 1) == numOfPoints)
			return;
		drawLine(renderer, Nodes[i].nodeCoord, Nodes[2 * (i+1)].nodeCoord);
	}
}

