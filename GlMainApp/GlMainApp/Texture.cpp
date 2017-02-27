#include "base.hpp"

#include "Tex.hpp"

//static GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f }; 	// ���������
static GLfloat LightAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 	// ���������
static GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };		// ��������
static GLfloat LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };	// ��������
static GLfloat LightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };	// ��Դλ��

void Texture::init()
{
	TexManager::loadTest();
	// me 
	// show
	TexManager::attach(L"me");

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	

	//glEnable(GL_AUTO_NORMAL);
	//glEnable(GL_NORMALIZE);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// ���û�����
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// ���������
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);	// ���������
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);	// ���ù�Դλ��
														
	glEnable(GL_LIGHTING);								// ���ù��պ͹�Դ
	glEnable(GL_LIGHT1);
}

static void drawBoxWithNorm()
{
	glBegin(GL_QUADS);
	// ǰ����
	glNormal3f(0.0f, 0.0f, 1.0f);								// ָ������ָ��۲���
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	// �����
	glNormal3f(0.0f, 0.0f, -1.0f);								// ָ�����߱���۲���
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	// ����
	glNormal3f(0.0f, 1.0f, 0.0f);								// ָ����������
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	// ����
	glNormal3f(0.0f, -1.0f, 0.0f);								// ָ�����߳���
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	// �Ҳ���
	glNormal3f(1.0f, 0.0f, 0.0f);								// ָ�����߳���
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	// �����
	glNormal3f(-1.0f, 0.0f, 0.0f);								// ָ�����߳���
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
}

void Texture::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glTranslatef(0.0f, 0.0f, -7.0f);
	glRotatef(getParam(), 1.0f, 1.0f, 0.0f);

	drawBoxWithNorm();
	//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	//glEnable(GL_TEXTURE_GEN_S);
	//glEnable(GL_TEXTURE_GEN_T);
	//glutSolidSphere(0.5, 30, 30);
	//glutsolidcube(2);
	//glutsolidteapot(2.0);
	glFlush();
}