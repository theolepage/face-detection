#include <iostream>
#include <err.h>

#include "Matrix/Matrix.h"
#include "HOG/HOG.h"
#include "Image/Image.h"
#include "GUI/GUI.h"

using namespace std;

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		errx(1, "Usage: ./FaceDetection [path]");
	}

	// Load image
	Image image;
	image.Load(argv[1]);

	// Compute HOG
	HOGExtractor extractor;
	extractor.ExtractHOG(image.grayscale);
	// extractor.Debug();

	// Start GUI
	GUI gui;
	gui.Start(image.width, image.height);
	gui.Show(image, extractor);

	return 0;
}