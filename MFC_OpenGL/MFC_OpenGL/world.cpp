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

bool World::init(HDC& h)
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

	hdc = h;
}

void World::draw()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清空颜色和深度缓冲
	int vsize = 500;
	glViewport(0, 0, vsize, vsize);
	
	cam.set();
	//glColor3f(1.0f, 1.0f, 1.0f);
	Cube(0.8).show();
	//Texes::detachAll();
	Coord(0.0, 0.0, 0.0, 3.5f).show();
	//Coord::globalshow();

	glFlush();
	SwapBuffers(hdc);
}

void World::fresh()
{
	//draw();
	glFlush();
	SwapBuffers(hdc);
}
void World::changeSize(int w, int h)
{

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
