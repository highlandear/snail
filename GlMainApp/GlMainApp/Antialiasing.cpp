#include "Impl.hpp"

void Antialiasing::init()
{

}

void Antialiasing::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(getParam(), 1.0f, 1.0f, 0.0f);
	glLineWidth(8.0);

	// �Ա�Ч��
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_BLEND);

	glColor3f(0.0f, 0.0f, 1.0f);
	glutWireCube(2.5);

	// ������Ч��
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glColor3f(1.0f, 0.0f, 1.0f);
	glutWireCube(2.2);
	
	glLoadIdentity();

	// �Ա�Ч��
	glColor3f(0.0f, 0.0f, 1.0f);				// ��ɫ ���õ�Ч��
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_POLYGON_SMOOTH);
	glDisable(GL_BLEND);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_DONT_CARE);

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);  
	glRotatef(getParam(), 1.0f, 0.0f, 1.0f); 
	
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();
	glPopMatrix();
	
	// ������Ч��
	glColor3f(1.0f, 0.0f, 1.0f);			  // ���ɫ��Ч����
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(-getParam(), 1.0f, 0.0f, 1.0f);

	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);

	glFlush();
}