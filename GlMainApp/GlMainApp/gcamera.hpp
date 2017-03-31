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
		ǰ��ƽ�� ���� p �� p->f ����f-p�������ƶ���
	*/
	void go(float sv);

	/*
		����ƽ�� �ӣ�f-p�� �� u �ķ��߷���
	*/
	void yaw(float sv);

	/*
		�� u ����
	*/
	void up(float sv);

	/*
		�� ������Ax, Ay, Az����ת rad ����
	*/
	void roll(float rad, float Ax, float Ay, float Az);

	/*
		������� ���� λ��
	*/
	void followMouse();

	bool isKeyDown(UINT k) { return KeyStatus::isKeyDown(k); }

	/*
		��ȡ�ƶ�����ֵ
	*/
	float getMoveSpeed();

	/*
		��ȡ�����ʣ����ȣ�
	*/
	float getRollSpeed();

private:
	Pos p;					// position where camera located
	Pos f;					// focus position
	Vec u;					// dirction vector to describe how to see "the up direction"
};