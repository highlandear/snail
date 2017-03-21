#pragma once

#include "xvector.hpp"
#include <vector>


template <class T>
class GMatrix
{
	GMatrix(T * p, int row, int col)
	{
		matrix.resize(row);

	}
	GVector<T> operator [] (int i) { return matrix[i];}
private:

	std::vector<GVector<T> > matrix;
};