#pragma once
#include"vector3D.hpp"

class Velocity
{
public:

	Velocity(float x, float y, float z, float v) : dir(x, y, z), value(v){}
	Velocity() : dir(0.0f, 0.0f, 0.0f), value(0.0f) {}
	void operator += (Velocity v)
	{
		dir += v.dir;
		value += v.value;
	}

	Velocity operator + (Velocity v)
	{
		Velocity ret;
		ret.value = value + v.value;
		ret.dir = dir + v.dir;
	}

private:

	float value;

	Dir dir;
};