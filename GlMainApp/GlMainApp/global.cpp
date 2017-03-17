#include "global.hpp"
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

namespace global
{
	// �����������
	GLfloat mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0 };       // ������ɫ
	GLfloat mat_diffuse[] = { 0.0f, 0.3f, 0.6f, 1.0f };      // ɢ����ɫ
	GLfloat mat_specular[] = { 1.0f, 0.0f, 1.0f, 1.0f };     // ���淴����ɫ
	GLfloat mat_shininess[] = { 10.0f };                     // ���淴��ָ��

	
	void setDefaultMaterial()
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);        // ���û�����ɫ
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);        // ����ɢ����ɫ
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);      // ���þ��淴����ɫ
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);    // ���þ��淴��ָ��
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