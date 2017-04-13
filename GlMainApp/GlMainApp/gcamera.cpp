#include "gcamera.hpp"
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>


void Camera::set()
{
	gluLookAt(p.x, p.y, p.z, f.x, f.y, f.z, u.x, u.y, u.z);
}

void Camera::go(float sv)
{
	Vector3D v = f - p;
	v.normalize();

	f += v * sv;
	p += v * sv;
}

void Camera::yaw(float sv)
{
	Dir v =  u * (f - p);
	v.normalize();

	f += v * sv;
	p += v * sv;
}

void Camera::up(float sv)
{
	Vec v = u * sv;

	f += v;
	p += v;
}

void Camera::roll(float a, float x, float y, float z)
{
	Vec v = f - p;
	Vec vta = v.roll(a, x, y, z);

	f = p + vta;
}

void Camera::followMouse()
{
	POINT mp;
	GetCursorPos(&mp);

	POINT mid = { GetSystemMetrics(SM_CXSCREEN) >> 1 , GetSystemMetrics(SM_CYSCREEN) >> 1 };

	if (mp.x == mid.x && mp.y == mid.y)
		return;

	SetCursorPos(mid.x, mid.y);

	float angY = (float)(mid.x - mp.x) / 1000.0f;
	float angX = (float)(mid.y - mp.y) / 1000.0f;
	roll(angY, 0.0f, 1.0f, 0.0f);

	Vec axis = (f - p) * u;
	axis.normalize();

	if (angX > 1.0f) angX = 1.0f;
	if (angX < -1.0) angX = -1.0f;

	roll(angX, axis.x, axis.y, axis.z);	
}

void Camera::update()
{
	// 前后
	if (isKeyDown('W'))
		go(getMoveSpeed());
	else if (isKeyDown('S'))
		go(- getMoveSpeed());

	// 左右
	if (isKeyDown('A'))
		yaw(getMoveSpeed());
	else if (isKeyDown('D'))
		yaw(- getMoveSpeed());

	// 上下
	if (isKeyDown(VK_UP))
		up(getMoveSpeed());
	else if (isKeyDown(VK_DOWN))
		up(-getMoveSpeed());

	// 顺逆 时钟
	if (isKeyDown(VK_LEFT))
		roll(getRollSpeed(), 0.0f, 1.0f, 0.0f);
	else if (isKeyDown(VK_RIGHT))
		roll(- getRollSpeed(), 0.0f, 1.0f, 0.0f);
	
	// Ctrl 键，跟踪鼠标
	if (isKeyDown(VK_CONTROL))
		followMouse();

}

float Camera::getMoveSpeed()
{
	return isKeyDown(VK_SHIFT) ? 3.0f : 1.5f;
}

float Camera::getRollSpeed()
{
	return isKeyDown(VK_SHIFT) ? 0.01f : 0.003f;
}