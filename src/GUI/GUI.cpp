#include <iostream>
#include <SDL2/SDL.h>

#include "../Image/Image.h"
#include "GUI.h"

using namespace std;

void GUI::Start(int width, int height)
{
	SDL_Window *window;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
}

void GUI::Show(Image image)
{
	for (int y = 0; y < image.height; y++)
	{
		for (int x = 0; x < image.width; x++)
		{
			unsigned char color = image.grayscale.data[y][x];
			SDL_SetRenderDrawColor(renderer, color, color, color, 255);
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}
	SDL_RenderPresent(renderer);
	Wait();
}

void GUI::Wait()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	while (event.type != SDL_QUIT)
	{
		SDL_PollEvent(&event);
	}
}