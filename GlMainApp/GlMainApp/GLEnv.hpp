#pragma once
#include "base.hpp"

class GLEnv
{
public:
	bool init(HWND h, int bitDepth);

	void glshape(int w, int h);

	void gldraw() { imp.draw(); SwapBuffers(m_hDC); };

private:
	HWND m_hWnd;

	HDC m_hDC;

	static Basic imp;

	static PIXELFORMATDESCRIPTOR GLEnv::pfd;
};