#pragma once
#include "stdafx.h"
#include <sstream>

namespace Helper
{
	static GLfloat mult = 1.0f;
	static GLfloat wsize = 1.0f * mult;
	static GLfloat step = 0.05f * mult;
	static GLfloat left = -1.0 * mult;
	static GLfloat cury = wsize;
	
	void print(GLfloat x, GLfloat y, const char * str)
	{
		glRasterPos2f(x, y);
		for (int i = 0; i < strlen(str); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *(str + i));
	}
	void print(GLfloat x, GLfloat y,GLfloat z, const char * str)
	{
		glRasterPos3f(x, y, z);
		for (int i = 0; i < strlen(str); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *(str + i));
	}

	void print(const char * mes)
	{
		print(left, cury, mes);
		cury -= step;
	}

	void reset()
	{
		cury = wsize;
	}

	template <typename T>
	std::string getlog(T v)
	{
		std::stringstream os;
		os << v;

		return os.str();
	}

	template <typename T>
	void printSquareMatrix(const T m[], size_t n)
	{
		std::stringstream os;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				os << (m[i*n + j]) << "\t#";
			}
			print(os.str().c_str());
			os.str("");
			
		}
	}
	void showViewMatrix()
	{
		GLfloat m[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		printSquareMatrix(m, 4);
	}

	void showProjectionMatrix()
	{
		GLfloat m[16];
		glGetFloatv(GL_PROJECTION_MATRIX, m);
		printSquareMatrix(m, 4);
	}

	void show()
	{
		print("--view--");
		showViewMatrix();
		print("--proj--");
		showProjectionMatrix();
	}
	
	void debug(std::wstring ws)
	{
		OutputDebugString(ws.c_str());
	}

	void debug(unsigned char m[], int n)
	{
		std::wstringstream os;
		for (int i = 0; i < n; i++)
		{
			os << m[i] << "\t";
		}
		os << std::endl;

		debug(os.str());
	}
}