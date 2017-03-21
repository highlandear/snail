#pragma once
#include "vector3D.hpp"
//#include "speed.hpp"

class Camera
{
public:
	void set();

	Camera(Pos& s0, Pos& f0, Dir& v0) : p(s0), f(f0), u(v0) {}

	Camera(Pos& s0, Pos& f0) :p(s0), f(f0), u(Dir(0.0f, 1.0f, 0.0f)) {}

	Camera(Pos& s0) :p(s0), f(Pos(0.0f, 0.0f, 0.0f)), u(Dir(0.0f, 1.0f, 0.0f)) {}

	Camera() {}

	Camera( float px, float py, float pz,
			float dx, float dy, float dz,
			float ux, float uy, float uz)
		: p(px, py, pz), f(dx, dy, dz), u(ux, uy, uz) {}
public:
	/*
		屏幕 z 轴运动
	*/
	void go(float sv);

	/*
		屏幕 x 轴运动
	*/
	void yaw(float sv);

	/*
		屏幕 y 轴运动
	*/
	void up(float sv);

	void dup(float sv);

	void roll(float a, float x, float y, float z);

	void setViewByMouse();

private:
	Pos p;					// position where camera located
	Pos f;					// focus direction
	Vec u;					// dirction vector to describe how to see "the up direction"
};