#pragma once
#include <windows.h>

class GLEnv
{
public:
	bool init(HWND h, int bitDepth);

	void glshape(int w, int h);

	void gldraw();

private:
	HWND m_hWnd;

	HDC m_hDC;

	static PIXELFORMATDESCRIPTOR GLEnv::pfd;
};