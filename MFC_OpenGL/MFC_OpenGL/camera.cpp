#include "stdafx.h"
#include "camera.hpp"

void Camera::set() const
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(150.0f, 2.0f, 100.0, 100.0f);			//设置透视投影矩阵  

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(p.x, p.y, p.z, f.x, f.y, f.z, v.x, v.y, v.z);

}
