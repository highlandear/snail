#include "Impl.hpp"
#include "global.hpp"
#include "tex.hpp"
#include "gout.hpp"

PFNGLACTIVETEXTUREARBPROC      Emboss::glActiveTextureARB = NULL;
PFNGLMULTITEXCOORD2FARBPROC    Emboss::glMultiTexCoord2fARB = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC Emboss::glClientActiveTextureARB = NULL;

void Emboss::init()
{
	if (!gout::isExtSupported("GL_ARB_multitexture"))
		return;

	glActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");
	glClientActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glClientActiveTextureARB");

	if (!glActiveTextureARB || !glMultiTexCoord2fARB || !glClientActiveTextureARB)
		return;

	global::gset();

	TexManager::loadTgaTexrure(L"wf", L"tex\\woodfloor.tga");
	
	if (!TexManager::attach(L"wf"))
		return;

	global::setDefaultLight();

	global::setDefaultMaterial();

}

void Emboss::update()
{
	Impl::update();
}

void Emboss::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(0.0f, 0.0f, -7.0f);
	glRotatef(getParam(), 1.0f, 1.0f, 0.0f);

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

	glFlush();
}