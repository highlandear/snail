#pragma once
#include <cmath>

#define _MATH_PI  3.1415

#define _DEG2RAD(d) ((d) * (_MATH_PI / 180.0f))
#define _RAD2DEG(r) ((r) * (180.0f / _MATH_PI))

class gmath
{
public:
	static int irand();

	static float frand();
	
	// 角度制求正余弦
	static float dsin(float degree)
	{
		return sinf(_DEG2RAD(degree));
	}

	static float dcos(float degree)
	{
		return cosf(_DEG2RAD(degree));
	}

	/*
		双线性插值公式
		f(x,y)= f(0, 0)(1 - x)(1 - y) + f(1, 0)x(1 - y) + f(0, 1)(1 - x)y + f(1, 1)xy
	*/
	static float bili_interpolation(float f00, float f01, float f10, float f11, float x, float y)
	{
		return f00 * (1.0f - x) * (1.0f - y) + f01 * (1.0f - x) * y + f10 * x * (1.0f - y) + f11 * x * y;
	}

};