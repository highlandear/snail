#include "Impl.hpp"
#include "global.hpp"
#include "tex.hpp"
#include "gout.hpp"
#include "base.hpp"

#include "illuminant.hpp"

PFNGLACTIVETEXTUREARBPROC      Emboss::glActiveTextureARB = NULL;
PFNGLMULTITEXCOORD2FARBPROC    Emboss::glMultiTexCoord2fARB = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC Emboss::glClientActiveTextureARB = NULL;

Emboss::VertexInfo Emboss::g_VerInfo[] =
{
	//   tu    tv     nx    ny     nz     x      y     z 
	{ 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,  -1.0f, -1.0f, 0.0f },
	{ 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, -1.0f, 0.0f },
	{ 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  -1.0f,  1.0f, 0.0f },
	{ 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,   1.0f,  1.0f, 0.0f }
};

void Emboss::init()
{
	if (! gout::isExtSupported("GL_ARB_multitexture"))
		return;

	glActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");
	glClientActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glClientActiveTextureARB");

	if (! glActiveTextureARB || !glMultiTexCoord2fARB || !glClientActiveTextureARB)
		return;

	global::gset();

	TexManager::loadTgaTexrure(L"woodfloor", L"tex\\woodfloor.tga");
	
	if (! TexManager::attach(L"woodfloor"))
		return;

	LightManager::onDefault();
	m_Light = LightManager::getDefault();
	GLfloat lp [] = { -2.0f, 0.0f, 0.0f, 1.0f };	// ��Դλ��
	m_Light.setPosV(lp);
}

void Emboss::update()
{
	if (isKeyDown('L'))
		LightManager::disable();
	else
		LightManager::enable();

	Impl::update();
}
void drawCube()
{
	glBegin(GL_QUADS);
	{
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
	}
	glEnd();
}

void Emboss::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	TexManager::disable();
	GLboolean e = LightManager::isEnabled();
	
	LightManager::disable();
	
	float p[4];
	m_Light.getPosV(p);
	glTranslatef(p[0] , p[1], -5.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	gdraw::drawBall(0.2);

	glTranslatef(2.0f, 0.0f, -2.0f);
	glRotatef(getParam(), 1.0f, 1.0f, 0.0f);

	
	if(e)
		LightManager::enable();
	TexManager::enable();
	drawCube();


	glFlush();
}