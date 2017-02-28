#include "Impl.hpp"
#include "Base.hpp"

// ��ʾ�˶���Դ��R/G/B����λ��
static float lightPositionR[] = { 0.0f, 0.0f, 5.0f, 1.0f };
static float lightPositionG[] = { 0.0f, 0.0f, 5.0f, 1.0f };
static float lightPositionB[] = { 0.0f, 0.0f, 5.0f, 1.0f };

// ����������Դ�������
static float diffuseLightR[] = { 1.0f, 0.0f, 0.0f, 1.0f };
static float diffuseLightG[] = { 0.0f, 1.0f, 0.0f, 1.0f };
static float diffuseLightB[] = { 0.0f, 0.0f, 1.0f, 1.0f };

// ����������Դ�ľ����
static float specularLightR[] = { 1.0f, 0.0f, 0.0f, 1.0f };
static float specularLightG[] = { 0.0f, 1.0f, 0.0f, 1.0f };
static float specularLightB[] = { 0.0f, 0.0f, 1.0f, 1.0f };

// һ��Ĭ�ϵĹ�Դ
static float diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
static float specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
static float lightPosition[] = { 0.0f, 0.0f, 10.0f, 1.0f };

void Light::init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);

	// ����0�Ź�Դ 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	// ����1�Ź�Դ -> ���Դ
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLightR);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLightR);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPositionR);

	// ����2�Ź�Դ -> ��ɫ
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLightG);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularLightG);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPositionG);

	// ����3�Ź�Դ -> ��ɫ
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLightB);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specularLightB);
	glLightfv(GL_LIGHT3, GL_POSITION, lightPositionB);

	glEnable(GL_LIGHT0);
}

void Light::update()
{
	if (isKeyDown('R'))
	{
		glDisable(GL_LIGHT1);
	}
	else
	{
		glEnable(GL_LIGHT1);
		reto(m_bRedX, 10);
		reto(m_bRedY, 5);
	}

	if (isKeyDown('G'))
	{
		glDisable(GL_LIGHT2);
	}
	else
	{
		glEnable(GL_LIGHT2);
		reto(m_bGreenX, 10);
		reto(m_bGreenY, 15);
	}

	if (isKeyDown('B'))
	{
		glDisable(GL_LIGHT3);
	}
	else
	{
		glEnable(GL_LIGHT3);
		reto(m_bBlueX, 10);
		reto(m_bBlueY, 10);
	}
}

void Light::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -10.0f);

	glPushMatrix();
	// ��ת��ɫ��Դ��
	glRotatef(m_bRedX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_bRedY, 0.0f, 1.0f, 0.0f);

	// ���ú�ɫ��Դλ��
	glLightfv(GL_LIGHT1, GL_POSITION, lightPositionR);

	// �ڹ�Դλ�ô�����һ��������Դ
	glTranslatef(lightPositionR[0], lightPositionR[1], lightPositionR[2]);
	glColor3f(1.0f, 0.0f, 0.0f);

	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);			// �ȹرչ���
	glutSolidSphere(0.2, 50, 50);
	glEnable(GL_LIGHTING);			// �����ù���
	glPopAttrib();
	glPopMatrix();

	// ��ɫ��Դ
	glPushMatrix();

	// ��ת��ɫ��Դ��
	glRotatef(m_bGreenX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_bGreenY, 0.0f, 1.0f, 0.0f);

	// ������ɫ��Դλ��
	glLightfv(GL_LIGHT2, GL_POSITION, lightPositionG);

	// �ڹ�Դλ�ô�����һ��������Դ
	glTranslatef(lightPositionG[0], lightPositionG[1], lightPositionG[2]);
	glColor3f(0.0f, 1.0f, 0.0f);	// ��ɫ

	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);			// �رչ���
	glutSolidSphere(0.1, 50, 50);
	glEnable(GL_LIGHTING);			// ���ù���
	glPopAttrib();
	glPopMatrix();

	// ��ɫ��Դ
	glPushMatrix();

	/// ��ת��ɫ��Դ��
	glRotatef(m_bBlueX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_bBlueY, 0.0f, 1.0f, 0.0f);

	// ������ɫ��Դλ��
	glLightfv(GL_LIGHT3, GL_POSITION, lightPositionB);

	// �ڹ�Դλ�ô�����һ��������Դ
	glTranslatef(lightPositionB[0], lightPositionB[1], lightPositionB[2]);
	glColor3f(0.0f, 0.0f, 1.0f);	// ��ɫ

	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);			// �رչ���
	glutSolidSphere(0.1, 50, 50);
	glEnable(GL_LIGHTING);			// ���ù���
	glPopAttrib();
	glPopMatrix();

	// ����һ������
	glPushMatrix();

	// ������ת
	glRotatef(getParam(), 1.0f, 0.0f, 0.0f);
	glRotatef(getParam(), 0.0f, 1.0f, 0.0f);
	glRotatef(getParam(), 0.0f, 0.0f, 1.0f);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.4, 50, 50);
	gdraw::drawBall(0.4);
	glPopMatrix();
	glFlush();
}