#pragma once
#include "tuple.hpp"
#include <cmath>

struct Vector3D : public Triple<float>
{
	Vector3D(float x0, float y0, float z0) : Triple(x0, y0, z0) {}

	Vector3D() : Triple(0.0f, 0.0f, 0.0f) {}

	// ���
	float X(Vector3D & v) { return (x * v.x + y * v.y + z * v.z); }

	// ���
	Vector3D & operator * (Vector3D & v)
	{
		Vector3D vec;

		vec.x = y * v.z - z * v.y;
		vec.y = z * v.x - x * v.z;
		vec.z = x * v.y - y * v.x;

		return vec;
	}

	// ģ��
	float len()
	{
		return sqrtf(x*x + y*y + z*z);
	}

	// ��һ��
	Vector3D Vector3D::normalize()
	{
		float ln = len();                  /**< ������������ */
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

	Vector3D operator - (const Vector3D & v)
	{
		Vector3D vec;

		vec.x = x - v.x;
		vec.y = y - v.y;
		vec.z = z - v.z;

		return vec;
	}
	
	// ����
	Vector3D operator *(float scale)
	{
		x = x * scale;
		y = y * scale;
		z = z * scale;

		return *this;
	}

	// ����
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

	// ����
	Vector3D operator -()
	{
		Vector3D vec(-x, -y, -z);
		return vec;
	}
};