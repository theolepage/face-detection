#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
	int lines, columns;
	public:
		unsigned char** data;
		void Create(int lines, int columns);
		void Print();
};

#endif