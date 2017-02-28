#include "EnvConfig.hpp"
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

namespace EnvConfig
{
	GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };	// 环境光参数
	GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };	// 漫射光参数
	GLfloat LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };	// 镜面光参数
	GLfloat LightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };	// 光源位置

															// 定义材质属性
	GLfloat mat_ambient[] = { 0.0,0.1,0.8,1.0 };            // 环境颜色
	GLfloat mat_diffuse[] = { 0.0,0.3,0.6,1.0 };            // 散射颜色
	GLfloat mat_specular[] = { 1.0,0.0,1.0,1.0 };           // 镜面反射颜色
	GLfloat mat_shininess[] = { 10.0 };                     // 镜面反射指数

	void shutDown() 
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT1);
	}

	void setDefault()
	{
		setDefaultLight();
		setDefaultMaterial();
	}

	void setDefaultLight()
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT1);

		glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);			// 设置环境光
		glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);			// 设置漫射光
		glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);		// 设置漫射光
		glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);		// 设置光源位置
	}

	void setDefaultMaterial()
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);        // 设置环境颜色
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);        // 设置散射颜色
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);      // 设置镜面反射颜色
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);    // 设置镜面反射指数
	}


};