#include <iostream>
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../Matrix/Matrix.h"
#include "Image.h"

using namespace std;

void Image::__GetRGBSDLPixel(SDL_Surface *surface, unsigned x, unsigned y, Uint8 *r, Uint8 *g, Uint8 *b)
{
	Uint8 *p =
		(Uint8 *)surface->pixels +
		y * surface->pitch +
		x * surface->format->BytesPerPixel;
	Uint32 pixel = 0;

	switch (surface->format->BytesPerPixel)
	{
	case 1:
		pixel = *p;
		break;
	case 2:
		pixel = *(Uint16 *)p;
		break;
	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			pixel = p[0] << 16 | p[1] << 8 | p[2];
		else
			pixel = p[0] | p[1] << 8 | p[2] << 16;
		break;
	case 4:
		pixel = *(Uint32 *)p;
		break;
	}

	SDL_GetRGB(pixel, surface->format, r, g, b);
}

void Image::Load(char* path)
{
	// Load image
	SDL_Surface *imageSurface;
	imageSurface = IMG_Load(path);

	// Exit if error while loading image
	if (!imageSurface)
	{
		errx(1, "%s", IMG_GetError());
	}

	// Getting image size
	width = imageSurface->w;
	height = imageSurface->h;

	// Create a grayscale matrix from the SDL surface
	Matrix grayscaleMatrix;
	grayscaleMatrix.Create(height, width);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Uint8 r, g, b;
			__GetRGBSDLPixel(imageSurface, x, y, &r, &g, &b);
			grayscaleMatrix.data[y][x] = (0.3 * r) + (0.59 * g) + (0.11 * b);
		}
	}
	grayscale = grayscaleMatrix;
}