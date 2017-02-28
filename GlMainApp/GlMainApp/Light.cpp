#include "Impl.hpp"
#include "Base.hpp"

// 演示运动光源（R/G/B）的位置
static float lightPositionR[] = { 0.0f, 0.0f, 5.0f, 1.0f };
static float lightPositionG[] = { 0.0f, 0.0f, 5.0f, 1.0f };
static float lightPositionB[] = { 0.0f, 0.0f, 5.0f, 1.0f };

// 定义三个光源的漫射光
static float diffuseLightR[] = { 1.0f, 0.0f, 0.0f, 1.0f };
static float diffuseLightG[] = { 0.0f, 1.0f, 0.0f, 1.0f };
static float diffuseLightB[] = { 0.0f, 0.0f, 1.0f, 1.0f };

// 定义三个光源的镜面光
static float specularLightR[] = { 1.0f, 0.0f, 0.0f, 1.0f };
static float specularLightG[] = { 0.0f, 1.0f, 0.0f, 1.0f };
static float specularLightB[] = { 0.0f, 0.0f, 1.0f, 1.0f };

// 一个默认的光源
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

	// 设置0号光源 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	// 设置1号光源 -> 红光源
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLightR);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLightR);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPositionR);

	// 设置2号光源 -> 绿色
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLightG);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularLightG);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPositionG);

	// 设置3号光源 -> 蓝色
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
	// 旋转红色光源球
	glRotatef(m_bRedX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_bRedY, 0.0f, 1.0f, 0.0f);

	// 设置红色光源位置
	glLightfv(GL_LIGHT1, GL_POSITION, lightPositionR);

	// 在光源位置处绘制一个球代表光源
	glTranslatef(lightPositionR[0], lightPositionR[1], lightPositionR[2]);
	glColor3f(1.0f, 0.0f, 0.0f);

	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);			// 先关闭光照
	glutSolidSphere(0.2, 50, 50);
	glEnable(GL_LIGHTING);			// 再启用光照
	glPopAttrib();
	glPopMatrix();

	// 绿色光源
	glPushMatrix();

	// 旋转绿色光源球
	glRotatef(m_bGreenX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_bGreenY, 0.0f, 1.0f, 0.0f);

	// 设置绿色光源位置
	glLightfv(GL_LIGHT2, GL_POSITION, lightPositionG);

	// 在光源位置处绘制一个球代表光源
	glTranslatef(lightPositionG[0], lightPositionG[1], lightPositionG[2]);
	glColor3f(0.0f, 1.0f, 0.0f);	// 绿色

	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);			// 关闭光照
	glutSolidSphere(0.1, 50, 50);
	glEnable(GL_LIGHTING);			// 启用光照
	glPopAttrib();
	glPopMatrix();

	// 蓝色光源
	glPushMatrix();

	/// 旋转蓝色光源球
	glRotatef(m_bBlueX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_bBlueY, 0.0f, 1.0f, 0.0f);

	// 设置蓝色光源位置
	glLightfv(GL_LIGHT3, GL_POSITION, lightPositionB);

	// 在光源位置处绘制一个球代表光源
	glTranslatef(lightPositionB[0], lightPositionB[1], lightPositionB[2]);
	glColor3f(0.0f, 0.0f, 1.0f);	// 蓝色

	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);			// 关闭光照
	glutSolidSphere(0.1, 50, 50);
	glEnable(GL_LIGHTING);			// 启用光照
	glPopAttrib();
	glPopMatrix();

	// 绘制一个球体
	glPushMatrix();

	// 设置旋转
	glRotatef(getParam(), 1.0f, 0.0f, 0.0f);
	glRotatef(getParam(), 0.0f, 1.0f, 0.0f);
	glRotatef(getParam(), 0.0f, 0.0f, 1.0f);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.4, 50, 50);
	gdraw::drawBall(0.4);
	glPopMatrix();
	glFlush();
}