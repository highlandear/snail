#include "global.hpp"
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

namespace global
{
	// 定义材质属性
	GLfloat mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0 };       // 环境颜色
	GLfloat mat_diffuse[] = { 0.0f, 0.3f, 0.6f, 1.0f };      // 散射颜色
	GLfloat mat_specular[] = { 1.0f, 0.0f, 1.0f, 1.0f };     // 镜面反射颜色
	GLfloat mat_shininess[] = { 10.0f };                     // 镜面反射指数

	
	void setDefaultMaterial()
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);        // 设置环境颜色
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);        // 设置散射颜色
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);      // 设置镜面反射颜色
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);    // 设置镜面反射指数
	}

	void gset()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
		glClearDepth(1.0f);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	}

};