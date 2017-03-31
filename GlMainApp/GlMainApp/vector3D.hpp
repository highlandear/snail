#pragma once
#include "tuple.hpp"
#include <cmath>

typedef struct Vector3D : public Triple<float>
{
	Vector3D(float x0, float y0, float z0) : Triple(x0, y0, z0) {}

	Vector3D() : Triple(0.0f, 0.0f, 0.0f) {}

	// 点乘
	float X(Vector3D & v) { return (x * v.x + y * v.y + z * v.z); }

	// 叉乘
	Vector3D operator * (Vector3D & v)
	{
		Vector3D vec;

		vec.x = y * v.z - z * v.y;
		vec.y = z * v.x - x * v.z;
		vec.z = x * v.y - y * v.x;

		return vec;
	}

	// 模长
	float len()
	{
		return sqrtf(x*x + y*y + z*z);
	}

	// 归一化
	Vector3D Vector3D::normalize()
	{
		float ln = len();
		if (ln == 0) ln = 1;

		x /= ln;
		y /= ln;
		z /= ln;

		return *this;
	}

	Vector3D operator + (const Vector3D & v)
	{
		Vector3D vec;

		vec.x = x + v.x;
		vec.y = y + v.y;
		vec.z = z + v.z;

		return vec;
	}

	void operator += (const Vector3D & v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

	}

	void operator -= (const Vector3D & v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	Vector3D operator - (const Vector3D & v)
	{
		Vector3D vec;

		vec.x = x - v.x;
		vec.y = y - v.y;
		vec.z = z - v.z;

		return vec;
	}
	
	// 数乘
	void operator *= (float scale)
	{
		x *= scale;
		y *= scale;
		z *= scale;
	}

	// 数乘
	Vector3D operator * (float scale)
	{
		Vector3D vec;
		vec.x = x * scale;
		vec.y = y * scale;
		vec.z = z * scale;
		
		return vec;
	}
	// 数除
	Vector3D operator /(float scale)
	{
		if (scale != 0.0)
		{
			x = x / scale;
			y = y / scale;
			z = z / scale;
		}
		return *this;
	}

	// 负数
	Vector3D operator -()
	{
		return Vector3D(-x, -y, -z);
	}

	Vector3D roll(float angle, float x, float y, float z);

	Vector3D rihgtProduct(float m[3][3]);

} Pos, Dir, Vec;


typedef struct Vector2D : public Pair<float>
{

}Vec2D;

