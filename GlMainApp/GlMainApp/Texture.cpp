#include "base.hpp"

#include "Tex.hpp"

//static GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f }; 	// 环境光参数
static GLfloat LightAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 	// 环境光参数
static GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };		// 漫射光参数
static GLfloat LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };	// 镜面光参数
static GLfloat LightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };	// 光源位置

Texture::~Texture()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);	
	glDisable(GL_LIGHT1);
}

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

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// 设置环境光
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// 设置漫射光
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);	// 设置漫射光
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);	// 设置光源位置
														
	glEnable(GL_LIGHTING);								// 启用光照和光源
	glEnable(GL_LIGHT1);
}

static void drawBoxWithNorm(float r)
{
	glPushMatrix();
	glScalef(r, r, r);

	glBegin(GL_QUADS);
	// 前侧面
	glNormal3f(0.0f, 0.0f, 1.0f);								// 指定法线指向观察者
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	// 后侧面
	glNormal3f(0.0f, 0.0f, -1.0f);								// 指定法线背向观察者
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	// 顶面
	glNormal3f(0.0f, 1.0f, 0.0f);								// 指定法线向上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	// 底面
	glNormal3f(0.0f, -1.0f, 0.0f);								// 指定法线朝下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	// 右侧面
	glNormal3f(1.0f, 0.0f, 0.0f);								// 指定法线朝右
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	// 左侧面
	glNormal3f(-1.0f, 0.0f, 0.0f);								// 指定法线朝左
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
	glPopMatrix();
	glLoadIdentity();
}

void Texture::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, -7.0f);
		glRotatef(getParam(), 1.0f, 1.0f, 0.0f);
		drawBoxWithNorm(0.5);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(getParam(), 1.0f, 1.0f, 0.0f);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	drawBoxWithNorm(1);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
glPopMatrix();


	//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	//glEnable(GL_TEXTURE_GEN_S);
	//glEnable(GL_TEXTURE_GEN_T);
	//glutSolidSphere(0.5, 30, 30);
	//glutsolidcube(2);
	//glutsolidteapot(2.0);
	glFlush();
}