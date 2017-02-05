#pragma once

template <typename T>
struct Triple
{
	Triple(T x0, T y0, T z0) : x(x0), y(y0), z(z0) {}
	void operator () (float x0, float y0, float z0) {}
	T x;
	T y;
	T z;
};

struct Pos : public Triple<float>
{
	Pos(float x0, float y0, float z0) : Triple(x0, y0, z0) {}
	Pos() : Triple(0.0, 0.0, 0.0) {}

	void move(float x0, float y0, float z0)
	{
		x = x + x0;
		y = y + y0;
		z = z + y0;
	}

};

struct Dir : public Triple<float>
{
	Dir(float x0, float y0, float z0) : Triple(x0, y0, z0) {}
	Dir() : Triple(0, 0, 0) {}
};
