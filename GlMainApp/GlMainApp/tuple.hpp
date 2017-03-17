#pragma once

template <typename T>
struct Pair
{
	Pair(T x0, T y0) : x(x0), y(y0) {}
	void operator () (float x0, float y0) {}

	T x, y;
};

template <typename T>
struct Triple
{
	Triple(T x0, T y0, T z0) : x(x0), y(y0), z(z0) {}
	void operator () (float x0, float y0, float z0) {}
	Triple(Triple & t) { x = t.x; y = t.y; z = t.z; }
	Triple operator = (Triple & t) { x = t.x; y = t.y; z = t.z; }


	T x, y, z;
};

struct Pos : public Triple<float>
{
	Pos(float x0, float y0, float z0) : Triple(x0, y0, z0) {}
	Pos() : Triple(0.0f, 0.0f, 0.0f) {}
};

//
//struct Dir : public Triple<float>
//{
//	Dir(float x0, float y0, float z0) : Triple(x0, y0, z0) {}
//	Dir() : Triple(0.0f, 0.0f, 0.0f) {}
//};

struct Vector3D : public Triple<float>
{
	Vector3D(float x0, float y0, float z0) : Triple(x0, y0, z0) {}
	Vector3D() : Triple(0.0f, 0.0f, 0.0f) {}

	// µã³Ë
	float X(Vector3D & v) { return (x * v.x + y * v.y + z * v.z); }

	// ²æ³Ë
	Vector3D & operator * (Vector3D & v)
	{
		Vector3D vec;

		vec.x = y * v.z - z * v.y;
		vec.y = z * v.x - x * v.z;
		vec.z = x * v.y - y * v.x;

		return vec;
	}
};

struct TexCoord : public Pair<float>
{
	TexCoord(float x0, float y0) : Pair(x0, y0) {}
	TexCoord() : Pair(.0f, 0.0f) {}
};
