#include "stdafx.h"
#include "world.hpp"
#include "camera.hpp"
#include "tex.hpp"
#include "base.hpp"

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

World WorldManager::wd = World();

bool World::init(HWND hwnd, int wi, int hi)
{
	int pixelformat;
	hdc = GetDC(hwnd);
	if (NULL == hdc)
		return false;

	if (!(pixelformat = ChoosePixelFormat(hdc, &pfd)))
		return false;
	if (!SetPixelFormat(hdc, pixelformat, &pfd))
		return false;

	HGLRC hrc = wglCreateContext(hdc);
	if (NULL == hrc)
		return false;

	if (!wglMakeCurrent(hdc, hrc))
		return false;

	width = wi; 
	hight = hi;
	return true;
}

void World::draw()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清空颜色和深度缓冲
	glViewport(0, 0, 100, 100);
	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.f, 1.f, 0.f);	glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(0.f, 0.f, 1.f);	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();
	//cam.set();
	glColor3f(1.0f, 0.0f, 1.0f);
	/*Pot(0.8).show();
	Coord(0.0, 0.0, 0.0, 1.0f).show();*/
	//glutSolidTeapot(0.5f);
	glFlush();
	SwapBuffers(hdc);
}

void World::fresh()
{
	draw();
}
void World::changeSize(int w, int h)
{
	width = w;
	hight = h;
	draw();
}

void World::call(UINT v)
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
