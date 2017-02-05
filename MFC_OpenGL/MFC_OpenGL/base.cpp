#include "stdafx.h"
#include "base.hpp"
#include "tex.hpp"
#include "helper.hpp"

void Pot::show()
{
	//glutSolidTeapot(sizef);
	glutSolidCube(sizef);
}

void Cube::show()
{
	//glutSolidSphere(sizef, 50, 50);
	glutSolidCube(sizef);
/*
	GLUquadricObj *quadPlanet = gluNewQuadric();
	//glGenerateMipmap(GL_TEXTURE_2D);
	
	gluQuadricTexture(quadPlanet, GLU_TRUE);
	//glRotatef(angle, 0.0f, 1.0f, 0.0f);
	gluSphere(quadPlanet, sizef, 50, 50);
	*/
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
	Helper::print(0.0f, 0.0f, 0.1f, "X");
	

	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.0f, 1.0f, 0.0f);
	gluCylinder(objCylinder, 0.01, 0.01, sizef, 10, 5);         //y - 

	glTranslatef(0, 0, sizef);
	gluCylinder(objCylinder, 0.03, 0.01, 0.05, 10, 5);			//y >
	Helper::print(0.0f, 0.0f, 0.1f, "Y");
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	gluCylinder(objCylinder, 0.01, 0.01, sizef, 10, 5);         //z -

	glTranslatef(0, 0, sizef);
	gluCylinder(objCylinder, 0.03, 0.01, 0.05, 10, 5);			//z >
	Helper::print(0.0f, 0.0f, 0.1f, "Z");
	glPopMatrix();
}