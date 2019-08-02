#pragma once
#include <iostream>
#include <SDL.h>
#include "node.h"

void drawLine(SDL_Renderer* renderer, SDL_Point A, SDL_Point B) {
	
	SDL_RenderDrawLine(renderer, A.x, A.y, B.x, B.y);
}
void drawLines(SDL_Renderer* renderer, const std::vector<node>& Nodes) {
	int lastParent = Nodes.size() / 2 - 1;

	for (int i = 0; i <= lastParent; ++i) {
		drawLine(renderer, Nodes[i].nodeCoord, Nodes[2 * i + 1].nodeCoord);
		if (i == lastParent && 2 * (i + 1) == Nodes.size())
			return;
		drawLine(renderer, Nodes[i].nodeCoord, Nodes[2 * (i+1)].nodeCoord);
	}
}

void drawRect(SDL_Renderer* renderer, SDL_Rect r) {
	SDL_Point A, B, C,D;
	A = { r.x,r.y };
	B = { r.x + r.w,r.y };
	C = { r.x + r.w,r.y + r.h };
	D = { r.x, r.y + r.h };
	drawLine(renderer, A, B);
	drawLine(renderer, B, C);
	drawLine(renderer, C, D);
	drawLine(renderer, D, A);
}
