#include <iostream>
#include <math.h>

#include "../Matrix/Matrix.h"
#include "HOG.h"

using namespace std;

void HOG::Extract(Matrix matrix)
{
	char kernel[] = {-1, 0, 1};

	for(int y = 0; y < matrix.lines; y++)
	{
		for(int x = 0; x < matrix.columns; x++)
		{
			int gx =
				kernel[0] * matrix.GetBlindly(y, x - 1) +
				kernel[1] * matrix.GetBlindly(y, x) +
				kernel[2] * matrix.GetBlindly(y, x + 1);
			int gy =
				kernel[0] * matrix.GetBlindly(y - 1, x) +
				kernel[1] * matrix.GetBlindly(y, x) +
				kernel[2] * matrix.GetBlindly(y + 1, x);

			int magnitude = sqrt(gx * gx + gy * gy);
			int direction = atan2(gy, gx);
			// Current pixel has this magnitude and direction, how to store it
		}
	}
}