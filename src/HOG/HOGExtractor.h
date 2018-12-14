#ifndef HOG_EXTRACTOR_H
#define HOG_EXTRACTOR_H

#include "../Matrix/Matrix.h"
#include "HOG.h"

class HOGExtractor
{
	public:
		int numberOfHOG;
		HOG *listOfHOG;
		void ExtractHOG(Matrix matrix);
		void Debug();
};

#endif