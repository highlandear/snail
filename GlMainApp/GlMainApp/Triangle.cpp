#include "Impl.hpp"

void Triangle::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -6.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	/*
	glBegin(GL_TRIANGLES);
	{
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	}
	*/


	glEnd();
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(1.5f);
	glBegin(GL_POINTS);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.5f, 0.5f);
	glEnd();
	const float Pi = 3.1415926;
	float R = 1.0f;
	int n = 50;
	glBegin(GL_POLYGON);
	for (int i = 0; i<n; i++)
		glVertex2f(R*cos(2 * Pi / n*i), R*sin(2 * Pi / n*i));
	glEnd();

	glFlush();
}

void Triangle::init()
{

}