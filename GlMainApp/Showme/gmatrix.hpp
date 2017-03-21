#pragma once

#include <string>
#include <sstream>


#ifndef _SAFE_DEL_ARRAY
#define _SAFE_DEL_ARRAY(p) { if(p){delete[] (p);  (p)=NULL;} }
#endif

template <typename T>
class Matrix
{

public:
	~Matrix() { _SAFE_DEL_ARRAY(m); row = col = 0; }

	Matrix(int r, int c)
	{
		m = new T[r*c];
		row = r;
		col = c;
	}

	Matrix(T p[], int r, int c)
	{
		m = new T[r*c];
		row = r;
		col = c;

		for (int i = 0; i < r*c; i++)
			m[i] = p[i];
	}

	Matrix operator * (Matrix& m);

	Matrix operator + (Matrix& other)
	{
		Matrix ret = Matrix(row, col);
		for (int i = 0; i < row*col; i++)
		{
			ret.m[i] = m[i] + other.m[i];
		}

		return ret;
	}

	std::wstring toString()
	{
		std::wstringstream ws;
		for (int r = 0; r < row; r++)
		{
			for (int c = 0; c < col; c++)
			{
				ws << m[r * col + c] << "\t";
			}

			ws << "\n";
		}
		return ws.str();
	}

	T& at(int r, int c) { return m[r * col + c]; }

	Matrix (Matrix& other)
	{
		row = other.row;
		col = other.col;

		m = new T[row * col];
		for (int i = 0; i < row * col; i++)
			m[i] = other.m[i];
	}

	Matrix operator = (Matrix& other)
	{
		row = other.row;
		col = other.col;

		m = new T[row * col];
		for (int i = 0; i < row * col; i++)
			m[i] = other.m[i];
	}
	
private:
	T * m;
	int row, col;
};


template <typename T>
Matrix<T> Matrix<T>::operator * (Matrix<T>& other)
{
	Matrix ret = Matrix(row, other.col);

	for (int r = 0; r < ret.row; r++)
	{
		for (int c = 0; c < ret.col; c++)
		{
			ret.m[r * ret.col + c] = 
		}
	}

	return ret;
}

