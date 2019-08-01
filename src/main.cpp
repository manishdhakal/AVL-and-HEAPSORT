
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

int main(int argc, char *argv[]) {

	SDL_Window *window;                    // Declare a pointer
	bool quit = false;
	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
	TTF_Init();
	// Create an application window with the following settings:
	window = SDL_CreateWindow(
		"DSA",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		640,                               // width, in pixels
		480,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Renderer* renderer;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

	// Clear the entire screen to our selected color.
	SDL_RenderClear(renderer);

	// Up until now everything was drawn behind the scenes.
	// This will show the new, red contents of the window.
	SDL_RenderPresent(renderer);

	TTF_Font* Sans = TTF_OpenFont("../res/arial.ttf", 200);

	if (!Sans) {
		std::cout << TTF_GetError() << std::endl;
		return 1;
	}
	SDL_Color _color = { 0,0, 0 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "manish", _color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture
	SDL_FreeSurface(surfaceMessage);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 100; //controls the rect's x coordinate 
	Message_rect.y = 100; // controls the rect's y coordinte
	Message_rect.w = 100; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect


	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

	SDL_Event evnt;
	while (!quit) {

		//you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your textu


		while (SDL_PollEvent(&evnt)){
			if (evnt.type == SDL_QUIT)
				quit = true;
		}
	}

	// Close and destroy the window
	SDL_DestroyWindow(window);
	TTF_CloseFont(Sans);
	TTF_Quit();
	SDL_Quit();
	return 0;
}
