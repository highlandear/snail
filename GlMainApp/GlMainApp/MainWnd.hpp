#pragma once
#include <windows.h>
#include "mconfig.hpp"
#include "GLEnv.hpp"

class MainWnd
{	
	struct XYWH	{int x, y, wgl, hgl;} m_nDef = { 0, 0, 0, 0 };

public:

	~MainWnd() { if (NULL != m_pEnv) delete m_pEnv; m_pEnv = NULL; }

	MainWnd() : m_hWnd(0) { m_pEnv = new GLEnv(); }


	HWND getHwnd() { return m_hWnd; }

	void onKeyDown(UINT keyID);

	void onKeyUp(UINT keyID);

	void onMoving(LPARAM lParam);

	void onSizing(LPARAM lParam);

	void onSize(WPARAM wParam, LPARAM lParam);

	void onLButtonDown(LPARAM lParam);

	void onRButtonDown(LPARAM lParam);
	
	bool create(HINSTANCE hIns, LPCWSTR title, LPCWSTR cname);

	void maindraw() { m_pEnv->gldraw(); }

private:

	HWND	m_hWnd;
	GLEnv*	m_pEnv;

	bool m_bFull;

	static int SCREEN_MAX_X, SCREEN_MAX_Y;

	Setting config;
};