#pragma once
#include <windows.h>
#include "GLEnv.hpp"

class MainWnd
{	
	struct XYWH	{int x, y, wgl, hgl;} m_nDef = { 0, 0, 0, 0 };

public:

	~MainWnd() { if (NULL != m_pEnv) delete m_pEnv; m_pEnv = NULL; }

	MainWnd(HINSTANCE i, LPCWSTR t, LPCWSTR c) : m_hInst(i), m_szTitle(t), m_szClassName(c) , m_hWnd(0) 
	{
		m_pEnv = new GLEnv();
	}
	HWND getHwnd() { return m_hWnd; }

	void onKeyDown(UINT keyID);
	void onMoving(LPARAM lParam);
	void onSizing(LPARAM lParam);
	void onSize(WPARAM wParam, LPARAM lParam);
	
	void create(int b, bool f, int w, int h);
	void maindraw() { m_pEnv->gldraw(); }

private:
	HWND	m_hWnd;
	GLEnv*	m_pEnv;
	
private:
	HINSTANCE	m_hInst;
	LPCWSTR		m_szTitle;			
	LPCWSTR		m_szClassName;

	bool m_bFull;

	static int SCREEN_MAX_X, SCREEN_MAX_Y;
};