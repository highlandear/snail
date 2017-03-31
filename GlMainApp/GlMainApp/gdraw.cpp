#include "gdraw.hpp"
#include <gl/glut.h>
#include <gl/GL.h>
#include <vector>


void gdraw::drawBall(float radius)
{
	glutSolidSphere(radius, 50, 50);
}

void gdraw::drawBall(float radius, float x, float y, float z)
{
	glPushMatrix();
	{
		glTranslatef(x, y, z);
		glutSolidSphere(radius, 50, 50);
	}
	glPopMatrix();
}

void gdraw::drawCube(float size)
{
//	glutSolidCube(size);
}

void gdraw::drawCube(float size, float x, float y, float z)
{
	glPushMatrix();
	{
		glTranslatef(x, y, z);
	//	glutSolidCube(size);
	}
	glPopMatrix();
}

void gdraw::drawTeaPot(float size)
{
//	glutSolidTeapot(size);
}

void gdraw::drawTeaPot(float size, float x, float y, float z)
{
	glPushMatrix();
	{
		glTranslatef(x, y, z);
//		glutSolidTeapot(size);
	}
	glPopMatrix();
}

void gdraw::drawGrid(float field, float interval)
{
	glPushAttrib(GL_CURRENT_BIT);	// 保存当前属性
	glPushMatrix();                 // 压入堆栈

	glBegin(GL_LINES);
	float i = - field;
	while (i <= field)
	{
		glVertex3f(-field, 0, i);
		glVertex3f(field, 0, i);

		glVertex3f(i, 0, -field);
		glVertex3f(i, 0, field);

		i += interval;
	}
	glEnd();

	glPopMatrix();
	glPopAttrib();
}

void gdraw::drawCube()
{
	glBegin(GL_QUADS);
	{
		// 前侧面
		glNormal3f(0.0f, 0.0f, 1.0f);								// 指定法线指向观察者
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		// 后侧面
		glNormal3f(0.0f, 0.0f, -1.0f);								// 指定法线背向观察者
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
		// 顶面
		glNormal3f(0.0f, 1.0f, 0.0f);								// 指定法线向上
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
		// 底面
		glNormal3f(0.0f, -1.0f, 0.0f);								// 指定法线朝下
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		// 右侧面
		glNormal3f(1.0f, 0.0f, 0.0f);								// 指定法线朝右
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
		// 左侧面
		glNormal3f(-1.0f, 0.0f, 0.0f);								// 指定法线朝左
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	}
	glEnd();
}