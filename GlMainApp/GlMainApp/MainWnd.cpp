#include "MainWnd.hpp"
#include "keyStatus.hpp"

int MainWnd::SCREEN_MAX_X = GetSystemMetrics(SM_CXSCREEN);
int MainWnd::SCREEN_MAX_Y = GetSystemMetrics(SM_CYSCREEN);

bool MainWnd::create(HINSTANCE hIns, LPCWSTR title, LPCWSTR cname )
{
	int b = config.getColor();
	int w = config.getWidth();
	int h = config.getHight();
	int f = config.isFull();

	int x0 = f ? 0 : SCREEN_MAX_X > w ? (SCREEN_MAX_X - w) / 2 : 0;
	int y0 = f ? 0 : SCREEN_MAX_Y > h ? (SCREEN_MAX_Y - h) / 2 : 0;
	int w0 = f ? SCREEN_MAX_Y : w;
	int h0 = f ? SCREEN_MAX_X : h;

	RECT rect = { x0, y0, x0 + w0, y0 + h0 };		
	AdjustWindowRectEx(&rect, WS_TILEDWINDOW, 0, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
	x0 = rect.left;
	y0 = rect.top;

	w0 = rect.right - rect.left;
	h0 = rect.bottom - rect.top;
	
	m_nDef = { x0, y0, w, h };

	m_hWnd = CreateWindowW(cname, title, WS_OVERLAPPEDWINDOW, x0, y0, w0, h0, NULL, NULL, hIns, NULL);

	if (NULL == m_hWnd)
		return false;

	if (! m_pEnv->init(m_hWnd, b))
	{
		MessageBox(HWND_DESKTOP, L"gl errro", L"tip", MB_OK);
		return false;
	}
	
	m_pEnv->glshape(w, h);
	ShowWindow(m_hWnd, SW_NORMAL);
	UpdateWindow(m_hWnd);

	return true;
}

void MainWnd::onKeyDown(UINT keyID)
{
	KeyStatus::setKeyDown(keyID);
	if (keyID == VK_F1)
	{
		m_bFull =! m_bFull;

		int x = 0; int y = 0;
		int w = 0; int h = 0;
		if (m_bFull)
		{
			w = SCREEN_MAX_X;
			h = SCREEN_MAX_Y;
			SetWindowLong(m_hWnd, GWL_STYLE, WS_BORDER );
			
		}
		else
		{
			x = m_nDef.x; y = m_nDef.y;
			w = m_nDef.wgl; h = m_nDef.hgl;
			SetWindowLong(m_hWnd, GWL_STYLE, WS_TILEDWINDOW);
		}
		
		SetWindowPos(m_hWnd, HWND_TOPMOST, x, y, w, h, SWP_SHOWWINDOW);

		m_pEnv->glshape(m_nDef.wgl, m_nDef.hgl);
	}


	else if (keyID == VK_ESCAPE)
	{
		PostMessage(m_hWnd, WM_QUIT, 0, 0);
		//m_pEnv->glshape(m_nDef.wgl, m_nDef.hgl);
		//m_pEnv->gldraw();
	}
}

void MainWnd::onKeyUp(UINT keyID)
{
	KeyStatus::setKeyUp(keyID);
}

void MainWnd::onMoving(LPARAM lParam)
{
	RECT * pRect = (RECT *)lParam;
	m_nDef.x = pRect->left;
	m_nDef.y = pRect->top;
}

void MainWnd::onSizing(LPARAM lParam)
{
	RECT * pRect = (RECT *)lParam;
	
	m_nDef.x = pRect->left;
	m_nDef.y = pRect->top;

	m_nDef.wgl = pRect->right - pRect->left;
	m_nDef.hgl = pRect->bottom - pRect->top;
	m_pEnv->glshape(m_nDef.wgl, m_nDef.hgl);
}

void MainWnd::onSize(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case SIZE_MAXIMIZED:
	{
		m_nDef.wgl = LOWORD(lParam);
		m_nDef.hgl = HIWORD(lParam);
		m_pEnv->glshape(m_nDef.wgl, m_nDef.hgl);
	}break;
	case SIZE_RESTORED:
	{
		m_nDef.wgl = LOWORD(lParam);
		m_nDef.hgl = HIWORD(lParam);
		m_pEnv->glshape(m_nDef.wgl, m_nDef.hgl);
	}break;
	}
}

// TODO: 坐标拾取时再实现
void MainWnd::onLButtonDown(LPARAM lParam)
{
	//MessageBox(NULL, L"鼠标左键点击", L"Win32_Mouse", MB_OK);
}

void MainWnd::onRButtonDown(LPARAM lParam)
{

}

