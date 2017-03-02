#include "base.hpp"
#include <gl/glut.h>
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
	glutSolidCube(size);
}

void gdraw::drawCube(float size, float x, float y, float z)
{
	glPushMatrix();
	{
		glTranslatef(x, y, z);
		glutSolidCube(size);
	}
	glPopMatrix();
}

void gdraw::drawTeaPot(float size)
{
	glutSolidTeapot(size);
}

void gdraw::drawTeaPot(float size, float x, float y, float z)
{
	glPushMatrix();
	{
		glTranslatef(x, y, z);
		glutSolidTeapot(size);
	}
	glPopMatrix();
}

void gdraw::print(float x, float y, float z, const char * str)
{
	glRasterPos3f(x, y, z);
	for (int i = 0; i < strlen(str); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *(str + i));
}

void gdraw::wprint(float x, float y, float z, const wchar_t *str)
{
	glRasterPos3f(x, y, z);
	for (int i = 0; i < wcslen(str); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *(str + i));
}