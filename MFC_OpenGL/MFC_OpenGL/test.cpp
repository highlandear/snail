#include "stdafx.h"
#include "test.hpp"
#include "base.hpp"
#include "tex.hpp"
#include "camera.hpp"

GLfloat BaseTest::view = 0.0f;
void BaseTest::init()
{
	TexTest::loadAll();

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
}

void BaseTest::launch()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清空颜色和深度缓冲
	int vsize = 500;
	glViewport(0, 0, vsize, vsize);
	 
	CameraManager::getCam().set();

	glRotatef(view, 1, 0, 0);
	view = (view + 15) > 360 ? 0 : view + 15;
	glColor3f(1.0f, 1.0f, 1.0f);
	Texes::attach(L"C:\\Users\\hzs\\Desktop\\me\\2.jpg");
	Cube(0.8).show();
	Texes::detachAll();
	Coord(0.0, 0.0, 0.0, 3.5f).show();
}

void DrawSphere(GLint sphereNum)
{

		glutSolidSphere(0.5f, 200, 200);

}
void DrawModels(void)
{

	//绘制27个不同颜色的球体
	for (int r = 0; r < 3; r++)
	{
		for (int g = 0; g < 3; g++)
		{
			for (int b = 0; b < 3; b++)
			{
				glColor3f(r * 0.5f, g * 0.5f, b * 0.5f);

				glPushMatrix();
				glTranslatef(100.0f * r/1000 - 100.0f/1000,
					100.0f * g/1000 - 100.0f/1000,
					100.0f * b/1000 - 100.0f/1000);
				DrawSphere((r * 9) + (g * 3) + b);
				glPopMatrix();
			}
		}
	}


}
void BaseTest::show()
{

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清空颜色和深度缓冲
	int vsize = 500;
	glViewport(0, 0, vsize, vsize);

	DrawModels();
}

void BaseTest::up()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清空颜色和深度缓冲
	int vsize = 500;
	glViewport(0, 0, vsize, vsize);

	Camera c = CameraManager::getCam();
	c.up();
	c.set();
	//CameraManager::getCam().set();

	//glRotatef(view, 1, 0, 0);
	//view = (view + 15) > 360 ? 0 : view + 15;
	glColor3f(1.0f, 1.0f, 1.0f);
	//Texes::attach(L"C:\\Users\\hzs\\Desktop\\me\\2.jpg");
	Cube(1.5).show();
	Texes::detachAll();
	Coord(0.0, 0.0, 0.0, 3.5f).show();


}

void BaseTest::down()
{
	Camera c = CameraManager::getCam();
	c.down();
	c.set();
}