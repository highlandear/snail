#include "GLEnv.hpp"

//Light GLEnv::imp;

PIXELFORMATDESCRIPTOR GLEnv::pfd =
{
	sizeof(PIXELFORMATDESCRIPTOR),
	1,
	PFD_DRAW_TO_WINDOW |
	PFD_SUPPORT_OPENGL |
	PFD_STEREO |
	PFD_DOUBLEBUFFER,
	PFD_TYPE_RGBA,
	32,	
	0, 0, 0, 0, 0, 0,
	0,
	0,
	0,
	0, 0, 0, 0,	
	32,
	0,
	0,
	PFD_MAIN_PLANE,
	0,
	0, 0, 0
};

bool GLEnv::init(HWND h, int b)
{
	m_hWnd = h;
	if (NULL == m_hWnd)
		return false;

	m_hDC = GetDC(m_hWnd);
	if (NULL == m_hDC)
		return false;
	
	GLuint PixelFormat = ChoosePixelFormat(m_hDC, &pfd);
	if (0 == PixelFormat)
		return false;

	if (! SetPixelFormat(m_hDC, PixelFormat, &pfd))
		return false;

	HGLRC hrc = wglCreateContext(m_hDC);
	if (NULL == hrc)
		return false;

	if (!wglMakeCurrent(m_hDC, hrc))
		return false;
	
	m_pImp->init();

	return true;
}

void GLEnv::glshape(int w, int h)
{
	glViewport(0, 0, w, h);									/**< 重新设置视口 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w/h, 1.0f, 100.0f);	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
