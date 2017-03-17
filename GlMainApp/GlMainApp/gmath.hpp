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
};