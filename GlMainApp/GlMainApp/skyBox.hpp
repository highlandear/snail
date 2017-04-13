#pragma once
#include "gmath.hpp"
#include "vector3D.hpp"

class SkyBox
{
public:

	SkyBox(float x, float y, float z, float l, float w, float h) : x0(x), y0(y), z0(z), x_len(l), z_wid(w), y_hig(h) {}

	SkyBox() {}

	void init();

	void draw();

private:

	float x0, y0, z0;		// ��պ�ԭ�㣨�ס����󶥵㣩
	float x_len;			// x �᷽�� ��
	float z_wid;			// z �᷽�� ��
	float y_hig;			// y �᷽�� ��
};