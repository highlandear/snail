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

	float x0, y0, z0;		// 天空盒原点（底、后、左顶点）
	float x_len;			// x 轴方向 长
	float z_wid;			// z 轴方向 宽
	float y_hig;			// y 轴方向 高
};