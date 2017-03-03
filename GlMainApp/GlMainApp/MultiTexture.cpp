#include "Impl.hpp"
#include "gout.hpp"
#include "global.hpp"
#include "tex.hpp"

PFNGLMULTITEXCOORD2FVARBPROC MultiTexture::glMtcoord2ARB = NULL;
PFNGLACTIVETEXTUREARBPROC MultiTexture::glATARB = NULL;

bool MultiTexture::isSupported()
{
	return gout::isExtSupported("GL_ARB_multitexture");
}

void MultiTexture::init()
{
	if (!isSupported())
	{
		MessageBox(NULL, L"multi-texture is not supported", L"tip", MB_OK);
		return;
	}
	glATARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	if (NULL == glATARB)
		return;

	glMtcoord2ARB = (PFNGLMULTITEXCOORD2FVARBPROC)wglGetProcAddress("glMultiTexCoord2fvARB");
	if (NULL == glMtcoord2ARB)
		return;

	global::gset();

	TexManager::loadBmpTexrure(L"sea", L"tex\\sea.bmp");
	TexManager::loadBmpTexrure(L"leaf", L"tex\\leaf.bmp");
	TexManager::loadBmpTexrure(L"galaxy", L"tex\\galaxy.bmp");
	TexManager::loadBmpTexrure(L"web", L"tex\\web.bmp");
	TexManager::loadBmpTexrure(L"wall", L"tex\\wall.bmp");
	TexManager::loadBmpTexrure(L"fog", L"tex\\fog.bmp");
	TexManager::loadBmpTexrure(L"lake", L"tex\\lake.bmp");
	TexManager::loadBmpTexrure(L"wall", L"tex\\wall.bmp");
	TexManager::loadBmpTexrure(L"sun", L"tex\\sun.bmp");

	TexManager::loadRawTexrure(L"raw");
}

void MultiTexture::update()
{
	m_fMove += 0.005f;
}

GLfloat left_up[] = { 0.0f, 1.0f };
GLfloat lef_down[] = { 0.0f, 0.0f };
GLfloat righ_down[] = { 1.0f, 0.0f };
GLfloat righ_up[] = { 1.0f, 1.0f };

void MultiTexture::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -10.0f);

	glATARB(GL_TEXTURE0_ARB);
	TexManager::attach(L"wall");

	glATARB(GL_TEXTURE1_ARB);
	TexManager::attach(L"sun");

	glPushMatrix();
	glTranslatef(-2.5, 0, 0);
	glScalef(2.0f, 2.0f, 2.0f);
	glBegin(GL_QUADS);
	{
		glMtcoord2ARB(GL_TEXTURE0_ARB, left_up);
		glMtcoord2ARB(GL_TEXTURE1_ARB, left_up);
		glVertex3f(-1, 1, 0);

		glMtcoord2ARB(GL_TEXTURE0_ARB, lef_down);
		glMtcoord2ARB(GL_TEXTURE1_ARB, lef_down);
		glVertex3f(-1, -1, 0);

		glMtcoord2ARB(GL_TEXTURE0_ARB, righ_down);
		glMtcoord2ARB(GL_TEXTURE1_ARB, righ_down);
		glVertex3f(1, -1, 0);

		glMtcoord2ARB(GL_TEXTURE0_ARB, righ_up);
		glMtcoord2ARB(GL_TEXTURE1_ARB, righ_up);
		glVertex3f(1, 1, 0);
	}
	glEnd(); 
	glPopMatrix();


	glATARB(GL_TEXTURE0_ARB);
	TexManager::attach(L"lake");

	glATARB(GL_TEXTURE1_ARB);
	TexManager::attach(L"fog");

	glTranslatef(2.5, 0, 0);
	glScalef(2.0f, 2.0f, 2.0f);
	glBegin(GL_QUADS);
	{
		GLfloat cood[][2] =
		{
			{ 0.0f + m_fMove, 1.0f } ,
			{ 0.0f + m_fMove, 0.0f },
			{ 1.0f + m_fMove, 0.0f },
			{ 1.0f + m_fMove, 1.0f }
		};

		glMtcoord2ARB(GL_TEXTURE0_ARB, left_up);
		glMtcoord2ARB(GL_TEXTURE1_ARB, cood[0]);
		glVertex3f(-1, 1, 0);

		glMtcoord2ARB(GL_TEXTURE0_ARB, lef_down );
		glMtcoord2ARB(GL_TEXTURE1_ARB, cood[1]);
		glVertex3f(-1, -1, 0);

		glMtcoord2ARB(GL_TEXTURE0_ARB, righ_down);
		glMtcoord2ARB(GL_TEXTURE1_ARB, cood[2]);
		glVertex3f(1, -1, 0);

		glMtcoord2ARB(GL_TEXTURE0_ARB, righ_up);
		glMtcoord2ARB(GL_TEXTURE1_ARB, cood[3]);
		glVertex3f(1, 1, 0);

	}
	glEnd();

	glFlush();
}

