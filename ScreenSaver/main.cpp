// BlockComp.cpp : Defines the entry point for the console application.
//

#include <string>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_syswm.h"
#include <SDL_image.h>

#include "mainApp.h"
using namespace std;

#define TICK_INTERVAL    30
static Uint32 next_time;

Uint32 time_left(void)
{
	Uint32 now;

	now = SDL_GetTicks();
	if (next_time <= now)
		return 0;
	else
		return next_time - now;
}

int main(int argc, char *argv[])
{

	MainApp app;
	//Event handler
	SDL_Event e;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	//inGameTimer = SDL_AddTimer(DEFAULT_RESOLUTION, ticktock, NULL);//how long have we been playing this game
	//inputTimer = SDL_AddTimer(DEFAULT_RESOLUTION, ticktock, NULL);//when was the last time someone pressed any sort of button
	//totalRuntime = SDL_AddTimer(DEFAULT_RESOLUTION, ticktock, NULL);//how long has the arcade been on

	app.InitWindow(640,480,false);
	app.InitScreens();

	next_time = SDL_GetTicks() + TICK_INTERVAL;
	bool done = false;
	while (!done)
	{
		while (SDL_PollEvent(&e)) 
		{
			/* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
			switch (e.type) {
			case SDL_KEYDOWN:
				printf("Key press detected\n");
				break;

			case SDL_KEYUP:
				printf("Key release detected\n");
				break;

			default:
				break;
			}
		}
		app.LogicUpdate();

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				done = true;
			}
		}

		SDL_Delay(time_left());
		next_time += TICK_INTERVAL;

		app.GraphicsUpdate();
	}

	/*SDL_RemoveTimer(inGameTimer);
	SDL_RemoveTimer(inputTimer);
	SDL_RemoveTimer(totalRuntime);*/




	IMG_Quit();

	SDL_Quit();
	return 0;
}