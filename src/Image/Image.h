#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include "../Matrix/Matrix.h"

class Image
{
	char* path;
	void __GetRGBSDLPixel(SDL_Surface *surface, unsigned x, unsigned y, Uint8 *r, Uint8 *g, Uint8 *b);
	public:
		int width, height;
		Matrix grayscale;
		void Load(char *path);
};

#endif