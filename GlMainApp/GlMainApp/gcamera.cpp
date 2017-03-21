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
	Dir v = Vector3D(0.0f, sv, 0.0f);

	f += v;
	p += v;
}

void Camera::dup(float sv)
{
	Dir v = Vector3D(0.0f, sv, 0.0f);

	f += v;
}

void Camera::roll(float a, float x, float y, float z)
{
	Vec v = f - p;
	Vec vta = v.roll(a, x, y, z);

	f = p + vta;
}

void Camera::setViewByMouse()

{
	POINT mousePos;									  /**< 保存当前鼠标位置 */
	int middleX = GetSystemMetrics(SM_CXSCREEN) >> 1; /**< 得到屏幕宽度的一半 */
	int middleY = GetSystemMetrics(SM_CYSCREEN) >> 1; /**< 得到屏幕高度的一半 */
	float angleY = 0.0f;							  /**< 摄像机左右旋转角度 */
	float angleZ = 0.0f;		                      /**< 摄像机上下旋转角度 */
	static float currentRotX = 0.0f;

	/** 得到当前鼠标位置 */
	GetCursorPos(&mousePos);
	ShowCursor(TRUE);

	/** 如果鼠标没有移动,则不用更新 */
	if ((mousePos.x == middleX) && (mousePos.y == middleY))
		return;

	/** 设置鼠标位置在屏幕中心 */
	SetCursorPos(middleX, middleY);

	/**< 得到鼠标移动方向 */
	angleY = (float)((middleX - mousePos.x)) / 1000.0f;
	angleZ = (float)((middleY - mousePos.y)) / 1000.0f;

	static float lastRotX = 0.0f;      /**< 用于保存旋转角度 */
	lastRotX = currentRotX;

	/** 跟踪摄像机上下旋转角度 */
	currentRotX += angleZ;

	/** 如果上下旋转弧度大于1.0,我们截取到1.0并旋转 */
	if (currentRotX > 1.0f)
	{
		currentRotX = 1.0f;

		/** 根据保存的角度旋转方向 */
		if (lastRotX != 1.0f)
		{
			/** 通过叉积找到与旋转方向垂直的向量 */
			Vec vAxis = f - p;
			vAxis = vAxis*(u);
			vAxis = vAxis.normalize();

			///旋转
			roll(1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}
	/** 如果旋转弧度小于-1.0,则也截取到-1.0并旋转 */
	else if (currentRotX < -1.0f)
	{
		currentRotX = -1.0f;

		if (lastRotX != -1.0f)
		{

			/** 通过叉积找到与旋转方向垂直的向量 */
			Vec vAxis = f - p;
			vAxis = vAxis*(u);
			vAxis = vAxis.normalize();

			///旋转
			roll(-1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}
	/** 否则就旋转angleZ度 */
	else
	{
		/** 找到与旋转方向垂直向量 */
		Vec vAxis = f - p;
		vAxis = vAxis*(u);
		vAxis = vAxis.normalize();

		///旋转
		roll(angleZ, vAxis.x, vAxis.y, vAxis.z);
	}

	/** 总是左右旋转摄像机 */
	roll(angleY, 0, 1, 0);
}