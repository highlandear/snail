#pragma once

template <typename T>
struct Pair
{
	Pair(T x0, T y0) : x(x0), y(y0) {}
	void operator () (float x0, float y0) {}
	Pair(const Pair & t) { x = t.x; y = t.y; }
	Pair operator = (const Pair & t) { x = t.x; y = t.y; return *this; }

	T x, y;
};

template <typename T>
struct Triple
{
	Triple() : x(0), y(0), z(0){}
	Triple(T x0, T y0, T z0) : x(x0), y(y0), z(z0) {}
	void operator () (float x0, float y0, float z0) {}
	Triple(const Triple & t) { x = t.x; y = t.y; z = t.z; }
	Triple operator = (const Triple & t) { x = t.x; y = t.y; z = t.z;  return *this; }

	int getDim() { return 3; }

	T x, y, z;
};

struct TexCoord : public Pair<float>
{
	TexCoord(float x0, float y0) : Pair(x0, y0) {}
	TexCoord() : Pair(.0f, 0.0f) {}
};
