// BlockComp.cpp : Defines the entry point for the console application.
//

#include <string>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_syswm.h"
#include <SDL_image.h>


using namespace std;


int main(int argc, char *argv[])
{

	SDL_Event e;
	int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	string title = "ScreenSaver";
	SDL_Window *window = SDL_CreateWindow(
		title.c_str(),                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		SCREEN_WIDTH,                               // width, in pixels
		SCREEN_HEIGHT,                               // height, in pixels
		SDL_WINDOW_RESIZABLE
	);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_Renderer* renderer{
		SDL_CreateRenderer(
			window, -1,
			SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE
		)
	};
	if (!renderer) {
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 0;
	}

	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	

	SDL_Delay(4000);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}