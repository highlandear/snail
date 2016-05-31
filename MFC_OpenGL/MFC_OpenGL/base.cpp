#include "stdafx.h"
#include "base.hpp"
#include "tex.hpp"
//#include "helper.hpp"

void Pot::show()
{
	glutSolidTeapot(sizef);
}

void Cube::show()
{
	glutSolidCube(sizef);
}

void Coord::globalshow()
{
	float ln = 1.0f;
	float sz = ln / 4;

	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(ln, 0.0f, 0.0f);

	glColor3f(0.0f, 10.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, ln, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, ln);

	glEnd();

}

void Coord::show()
{
	glTranslatef(x0, y0, z0);
	
	glPushMatrix();
	glRotatef(90, 0.0, 1.0, 0.0);
	GLUquadricObj *objCylinder = gluNewQuadric();
	glColor3f(1.0f, 0.0f, 0.0f);
	gluCylinder(objCylinder, 0.01, 0.01, sizef, 10, 5);         // x -
	
	glTranslatef(0, 0, sizef);
	gluCylinder(objCylinder, 0.03, 0.01, 0.05, 10, 5);			// x >

	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.0f, 1.0f, 0.0f);
	gluCylinder(objCylinder, 0.01, 0.01, sizef, 10, 5);         //y - 

	glTranslatef(0, 0, sizef);
	gluCylinder(objCylinder, 0.03, 0.01, 0.05, 10, 5);			//y >
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	gluCylinder(objCylinder, 0.01, 0.01, sizef, 10, 5);         //z -

	glTranslatef(0, 0, sizef);
	gluCylinder(objCylinder, 0.03, 0.01, 0.05, 10, 5);			//z >
	glPopMatrix();
}