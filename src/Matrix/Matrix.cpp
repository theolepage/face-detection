#include <iostream>

#include "Matrix.h"

using namespace std;

void Matrix::Create(int l, int c)
{
	// Update matrix variables
	lines = l;
	columns = c;

	// Allocate memory for two dimensional array of size lines*columns with 0 as values
	unsigned char** matrix = (unsigned char**)calloc(lines, sizeof(unsigned char*));
	for (int y = 0; y < lines; y++)
	{
		*(matrix + y) = (unsigned char*)calloc(columns, sizeof(unsigned char));
	}
	data = matrix;
}

void Matrix::Print()
{
	for(int y = 0; y < lines; y++)
	{
		for(int x = 0; x < columns; x++)
		{
			cout << +data[y][x] << " ";
		}
		cout << "\n";
	}
}

unsigned char Matrix::GetBlindly(int y, int x)
{
	if (y < 0 || y >= lines || x < 0 || x >= columns)
	{
		return 0;
	}
	return data[y][x];
}