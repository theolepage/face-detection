#include <iostream>
#include <err.h>

#include "Matrix/Matrix.h"
#include "Image/Image.h"
#include "GUI/GUI.h"

using namespace std;

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		errx(1, "Usage: ./FaceDetection [path]");
	}

	Image image;
	GUI gui;

	image.Load(argv[1]);
	gui.Start(image.width, image.height);
	gui.Show(image);

	return 0;
}