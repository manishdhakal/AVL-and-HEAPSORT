#pragma once
#include <SDL.h>
#include <vector>


struct node {
	SDL_Point nodeCoord;
	SDL_Rect arrRect;
	int value;

};

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

void addNode(std::vector<node>& nodes,int value, int W, int H) {
	int treeHeight = getheight(nodes.size() + 1);
	int newIndex = nodes.size(), parIndex;
	int last = nodes.size() - 1;
	node New;
	New.nodeCoord.y = 75 * treeHeight + 400;
	New.arrRect.h = 50;
	New.arrRect.w = 50;

	if (nodes.size() == 12) {
		New.arrRect.x = 50;
		New.arrRect.y = nodes[last].arrRect.y + 50;
	}
	else {
		New.arrRect.x = nodes[last].arrRect.x + 50;
		New.arrRect.y = nodes[last].arrRect.y;
	}
	if (newIndex % 2 == 0) {
		parIndex = newIndex / 2 - 1;
		New.nodeCoord.x = nodes[parIndex].nodeCoord.x + W / (int)pow(2, treeHeight + 1);

	}
	else {
		parIndex = newIndex / 2;
		New.nodeCoord.x = nodes[parIndex].nodeCoord.x - W / (int)pow(2, treeHeight + 1);

	}
	New.value = value;
	nodes.push_back(New);
}