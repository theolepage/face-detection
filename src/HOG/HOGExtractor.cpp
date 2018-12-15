#include <iostream>
#include <math.h>

#include "../Matrix/Matrix.h"
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
	int cellSize = 8;

	int height = matrix.lines - matrix.lines % cellSize;
	int width = matrix.columns - matrix.columns % cellSize;

	numberOfHOG = (height / cellSize) * (width / cellSize);
	int numberOfHOGCreated = 0;
	listOfHOG = (HOG*)calloc(numberOfHOG, sizeof(HOG));

	// Go through each pixel
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			// Create the HOG
			if(y % cellSize == 0 && x % cellSize == 0)
			{
				HOG hog;
				hog.x = x;
				hog.y = y;
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
			float direction = atan2(gy, gx) * (180 / 3.14159265) + 180;
			int angle = (int)direction % 180;

			float leftValue = (angle / 20.0) - (angle / 20);
			float rightValue = 1 - leftValue;
			int leftAngle = (angle / 20) % 9;
			int rightAngle = ((angle / 20) + 1) % 9;

			int currentHOGId = (y / cellSize) * (width / cellSize) + (x / cellSize);
			listOfHOG[currentHOGId].data[leftAngle] += round(leftValue * magnitude);
			listOfHOG[currentHOGId].data[rightAngle] += round(rightValue * magnitude);
		}
	}

	// Create 16x16 normalized blocks with all cells
	int chunkSize = 16;
	int ratio = 2 * chunkSize / cellSize;

	int numberOfHOGChunkCreated = 0;
	numberOfHOGChunk = numberOfHOG / ratio;
	listOfHOGChunk = (HOGChunk*)calloc(numberOfHOGChunk, sizeof(HOGChunk));

	for(int i = 0; i < numberOfHOG; i++)
	{
		HOG hog = listOfHOG[i];

		// Create the HOGChunk
		if (hog.y % chunkSize == 0 && hog.x % chunkSize == 0)
		{
			HOGChunk chunk;
			chunk.x = hog.x;
			chunk.y = hog.y;
			chunk.currentHistogramId = 0;
			chunk.length = 0;
			listOfHOGChunk[numberOfHOGChunkCreated] = chunk;
			numberOfHOGChunkCreated++;
		}

		// Update HOGChunk
		int currentHOGChunkId = (hog.y / chunkSize) * (width / chunkSize) + (hog.x / chunkSize);
		HOGChunk chunk = listOfHOGChunk[currentHOGChunkId];
		for (int k = 0; k < 9; k++)
		{
			chunk.data[chunk.currentHistogramId] = hog.data[k];
			chunk.length += hog.data[k] * hog.data[k];
			chunk.currentHistogramId++;
		}

		// Normalize HOGChunk when it is completed
		if (chunk.currentHistogramId == 9 * ratio)
		{
			chunk.length = sqrt(chunk.length);
			for (int k = 0; k < 9 * ratio; k++)
			{
				chunk.data[k] /= chunk.length;
			}
		}
	}
}