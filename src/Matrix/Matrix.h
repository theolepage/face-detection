#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
	public:
		int lines, columns;
		unsigned char** data;
		void Create(int lines, int columns);
		void Print();
		unsigned char GetBlindly(int y, int x);
};

#endif