#ifndef HOG_H
#define HOG_H

#include "../Matrix/Matrix.h"

class HOG
{
	public:
		int y, x;
		float *data = new float[9]();
};

class HOGChunk
{
	public:
		int y, x;
		int currentHistogramId, length;
		float *data = new float[4 * 9]();
};

class HOGExtractor
{
	public:
		int numberOfHOG;
		int numberOfHOGChunk;
		HOG* listOfHOG;
		HOGChunk* listOfHOGChunk;
		void ExtractHOG(Matrix matrix);
		void Debug();
};

#endif