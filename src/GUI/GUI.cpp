#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>

#include "../HOG/HOG.h"
#include "../Image/Image.h"
#include "GUI.h"

using namespace std;

void GUI::Start(int width, int height)
{
	SDL_Window *window;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
}

void GUI::Show(Image image, HOGExtractor extractor)
{
	// Draw image
	for (int y = 0; y < image.height; y++)
	{
		for (int x = 0; x < image.width; x++)
		{
			unsigned char color = image.grayscale.data[y][x];
			SDL_SetRenderDrawColor(renderer, color, color, color, 255);
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}

	// Draw HOG
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for (int i = 0; i < extractor.numberOfHOG; i++)
	{
		HOG hog = extractor.listOfHOG[i];
		int y = hog.y + 4;
		int x = hog.x + 4;

		int max = 0;
		for(int j = 0; j < 9; j++)
		{
			if (hog.data[j] > hog.data[max])
			{
				max = j;
			}
		}

		float angle = 90 + max * 20 * 3.14 / 180;
		if (hog.data[max] > 300)
		{
			SDL_RenderDrawLine(renderer, x, y, x + 4 * cos(angle), y + 4 * sin(angle));
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