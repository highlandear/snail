#pragma once
#include "vector3D.hpp"
#include "keyStatus.hpp"

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
	
	void update();

private:	
	/*
		前后平移 （从 p 延 p->f 即（f-p）方向移动）
	*/
	void go(float sv);

	/*
		左右平移 延（f-p） 和 u 的法线方向
	*/
	void yaw(float sv);

	/*
		延 u 方向
	*/
	void up(float sv);

	/*
		绕 向量（Ax, Ay, Az）旋转 rad 弧度
	*/
	void roll(float rad, float Ax, float Ay, float Az);

	/*
		根据鼠标 调节 位置
	*/
	void followMouse();

	bool isKeyDown(UINT k) { return KeyStatus::isKeyDown(k); }

	/*
		获取移动速率值
	*/
	float getMoveSpeed();

	/*
		获取角速率（弧度）
	*/
	float getRollSpeed();

private:
	Pos p;					// position where camera located
	Pos f;					// focus position
	Vec u;					// dirction vector to describe how to see "the up direction"
};