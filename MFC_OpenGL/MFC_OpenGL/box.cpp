
#include "stdafx.h"

#include "box.hpp"
#include "test.hpp"


static PIXELFORMATDESCRIPTOR pfd =
{
sizeof(PIXELFORMATDESCRIPTOR),
1,
PFD_DRAW_TO_WINDOW |
PFD_SUPPORT_OPENGL |
PFD_DOUBLEBUFFER,
PFD_TYPE_RGBA,
24 ,
0, 0, 0, 0, 0, 0,
0,
0,
0,
0, 0, 0, 0,
32 ,
0,
0,
PFD_MAIN_PLANE,
0,
0, 0, 0
};

bool BOX::init(HDC hdc)
{
	int pixelformat;

	if (!(pixelformat = ChoosePixelFormat(hdc, &pfd)))
		return false;
	if (!SetPixelFormat(hdc, pixelformat, &pfd))
		return false;

	HGLRC hrc = wglCreateContext(hdc);
	if (NULL == hrc)
		return false;

	if (!wglMakeCurrent(hdc, hrc))
		return false;
}

void BOX::draw(HDC hdc)
{
	BaseTest::init();
	//BaseTest::launch();
	BaseTest::show();
	glFlush();
	SwapBuffers(hdc);
}

void BOX::fresh(HDC hdc)
{
	BaseTest::launch();
	glFlush();
	SwapBuffers(hdc);
}
void BOX::changeSize(HDC hdc, int w, int h)
{

}

void BOX::call(UINT v)
{
	switch (v)
	{
	case VK_RIGHT:
	{
		MessageBox(NULL, L"ok", L"tips", MB_OK);

	}break;
	case 'D':
	{
		MessageBox(NULL, L"D", L"tips", MB_OK);
	}break;
	}
}
