#include "Impl.hpp"
#include "gout.hpp"
#include "global.hpp"
#include "tex.hpp"

PFNGLMULTITEXCOORD2FVARBPROC MultiTexture::glMtcoord2fvARB = NULL;
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

	glMtcoord2fvARB = (PFNGLMULTITEXCOORD2FVARBPROC)wglGetProcAddress("glMultiTexCoord2fvARB");
	if (NULL == glMtcoord2fvARB)
		return;

	global::gset();

	TexManager::loadBmpTexrure(L"wall", L"tex\\wall.bmp");
	TexManager::loadBmpTexrure(L"fog", L"tex\\fog.bmp");
	TexManager::loadBmpTexrure(L"lake", L"tex\\lake.bmp");
	TexManager::loadBmpTexrure(L"sun", L"tex\\sun.bmp");
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
		glMtcoord2fvARB(GL_TEXTURE0_ARB, left_up);
		glMtcoord2fvARB(GL_TEXTURE1_ARB, left_up);
		glVertex3f(-1, 1, 0);

		glMtcoord2fvARB(GL_TEXTURE0_ARB, lef_down);
		glMtcoord2fvARB(GL_TEXTURE1_ARB, lef_down);
		glVertex3f(-1, -1, 0);

		glMtcoord2fvARB(GL_TEXTURE0_ARB, righ_down);
		glMtcoord2fvARB(GL_TEXTURE1_ARB, righ_down);
		glVertex3f(1, -1, 0);

		glMtcoord2fvARB(GL_TEXTURE0_ARB, righ_up);
		glMtcoord2fvARB(GL_TEXTURE1_ARB, righ_up);
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

		glMtcoord2fvARB(GL_TEXTURE0_ARB, left_up);
		glMtcoord2fvARB(GL_TEXTURE1_ARB, cood[0]);
		glVertex3f(-1, 1, 0);

		glMtcoord2fvARB(GL_TEXTURE0_ARB, lef_down );
		glMtcoord2fvARB(GL_TEXTURE1_ARB, cood[1]);
		glVertex3f(-1, -1, 0);

		glMtcoord2fvARB(GL_TEXTURE0_ARB, righ_down);
		glMtcoord2fvARB(GL_TEXTURE1_ARB, cood[2]);
		glVertex3f(1, -1, 0);

		glMtcoord2fvARB(GL_TEXTURE0_ARB, righ_up);
		glMtcoord2fvARB(GL_TEXTURE1_ARB, cood[3]);
		glVertex3f(1, 1, 0);

	}
	glEnd();

	glFlush();
}

