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
	POINT mousePos;									  /**< ���浱ǰ���λ�� */
	int middleX = GetSystemMetrics(SM_CXSCREEN) >> 1; /**< �õ���Ļ��ȵ�һ�� */
	int middleY = GetSystemMetrics(SM_CYSCREEN) >> 1; /**< �õ���Ļ�߶ȵ�һ�� */
	float angleY = 0.0f;							  /**< �����������ת�Ƕ� */
	float angleZ = 0.0f;		                      /**< �����������ת�Ƕ� */
	static float currentRotX = 0.0f;

	/** �õ���ǰ���λ�� */
	GetCursorPos(&mousePos);
	ShowCursor(TRUE);

	/** ������û���ƶ�,���ø��� */
	if ((mousePos.x == middleX) && (mousePos.y == middleY))
		return;

	/** �������λ������Ļ���� */
	SetCursorPos(middleX, middleY);

	/**< �õ�����ƶ����� */
	angleY = (float)((middleX - mousePos.x)) / 1000.0f;
	angleZ = (float)((middleY - mousePos.y)) / 1000.0f;

	static float lastRotX = 0.0f;      /**< ���ڱ�����ת�Ƕ� */
	lastRotX = currentRotX;

	/** ���������������ת�Ƕ� */
	currentRotX += angleZ;

	/** ���������ת���ȴ���1.0,���ǽ�ȡ��1.0����ת */
	if (currentRotX > 1.0f)
	{
		currentRotX = 1.0f;

		/** ���ݱ���ĽǶ���ת���� */
		if (lastRotX != 1.0f)
		{
			/** ͨ������ҵ�����ת����ֱ������ */
			Vec vAxis = f - p;
			vAxis = vAxis*(u);
			vAxis = vAxis.normalize();

			///��ת
			roll(1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}
	/** �����ת����С��-1.0,��Ҳ��ȡ��-1.0����ת */
	else if (currentRotX < -1.0f)
	{
		currentRotX = -1.0f;

		if (lastRotX != -1.0f)
		{

			/** ͨ������ҵ�����ת����ֱ������ */
			Vec vAxis = f - p;
			vAxis = vAxis*(u);
			vAxis = vAxis.normalize();

			///��ת
			roll(-1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}
	/** �������תangleZ�� */
	else
	{
		/** �ҵ�����ת����ֱ���� */
		Vec vAxis = f - p;
		vAxis = vAxis*(u);
		vAxis = vAxis.normalize();

		///��ת
		roll(angleZ, vAxis.x, vAxis.y, vAxis.z);
	}

	/** ����������ת����� */
	roll(angleY, 0, 1, 0);
}