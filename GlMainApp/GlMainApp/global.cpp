#include "global.hpp"
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

namespace global
{
//	GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };	// ���������
	GLfloat LightAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };	// ���������
	GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };	// ��������
	GLfloat LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };	// ��������
	GLfloat LightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };	// ��Դλ��

															// �����������
	GLfloat mat_ambient[] = { 0.0,0.1,0.8,1.0 };            // ������ɫ
//	GLfloat mat_ambient[] = { 1.0f, 1.0f, 1.0f,1.0 };            // ������ɫ
	GLfloat mat_diffuse[] = { 0.0,0.3,0.6,1.0 };            // ɢ����ɫ
	GLfloat mat_specular[] = { 1.0,0.0,1.0,1.0 };           // ���淴����ɫ
	GLfloat mat_shininess[] = { 10.0 };                     // ���淴��ָ��

	void shutDefaultDown() 
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT1);
	}

	void setDefaultLight()
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT1);

		glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);			// ���û�����
		glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);			// ���������
		glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);		// ���������
		glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);		// ���ù�Դλ��
	}

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