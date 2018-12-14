#include <iostream>
#include <math.h>

#include "../Matrix/Matrix.h"
#include "HOGExtractor.h"
#include "HOG.h"

using namespace std;

void HOGExtractor::Debug()
{
	cout << "Number of HOG: " << numberOfHOG << "\n";
	for(int i = 0; i < numberOfHOG; i++)
	{
		HOG hog = listOfHOG[i];
		cout << "HOG at (" << hog.x << ", " << hog.y << ")\n";
		cout << "[";
		for(int j = 0; j < 8; j++)
		{
			cout << hog.data[j] << ", ";
		}
		cout << hog.data[8] << "]\n\n";
	}
}

void HOGExtractor::ExtractHOG(Matrix matrix)
{
	char kernel[] = {-1, 0, 1};

	int height = matrix.lines - matrix.lines % 8;
	int width = matrix.columns - matrix.columns % 8;

	numberOfHOG = (height / 8) * (width / 8);
	int numberOfHOGCreated = 0;
	listOfHOG = (HOG*)calloc(numberOfHOG, sizeof(HOG));

	// Go through each pixel
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			// Create the HOG
			if(y % 8 == 0 && x % 8 == 0)
			{
				HOG hog;
				hog.x = x / 8;
				hog.y = y / 8;
				listOfHOG[numberOfHOGCreated] = hog;
				numberOfHOGCreated++;
			}

			// Computer horizontal and vertical gradients for current pixel
			float gx =
				kernel[0] * matrix.GetBlindly(y, x - 1) +
				kernel[1] * matrix.GetBlindly(y, x) +
				kernel[2] * matrix.GetBlindly(y, x + 1);
			float gy =
				kernel[0] * matrix.GetBlindly(y - 1, x) +
				kernel[1] * matrix.GetBlindly(y, x) +
				kernel[2] * matrix.GetBlindly(y + 1, x);

			// Update the HOG
			float magnitude = sqrt(gx * gx + gy * gy);
			float direction = atan2(gy, gx) * (180 / 3.14159265);
			int angle = (int)direction % 180;

			float leftValue = (angle / 20.0) - (angle / 20);
			float rightValue = 1 - leftValue;
			int leftAngle = (angle / 20) % 9;
			int rightAngle = ((angle / 20) + 1) % 9;

			int currentHOGId = (y / 8) * (width / 8) + (x / 8);
			listOfHOG[currentHOGId].data[leftAngle] += round(leftValue * magnitude);
			listOfHOG[currentHOGId].data[rightAngle] += round(rightValue * magnitude);
		}
	}
}