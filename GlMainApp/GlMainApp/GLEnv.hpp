#pragma once
#include "Impl.hpp"

class GLEnv
{

public:
	
	GLEnv() { m_pImp = new _IMPL_CLASS(); }

	~GLEnv() { _SAFE_DEL(m_pImp); }

	bool init(HWND h, int bitDepth);

	void glshape(int w, int h);

	void gldraw() { m_pImp->draw(); m_pImp->update(); SwapBuffers(m_hDC); };

private:

	HWND m_hWnd;

	HDC m_hDC;

	Impl * m_pImp;

	static PIXELFORMATDESCRIPTOR GLEnv::pfd;
};