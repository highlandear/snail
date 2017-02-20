#include "MainWnd.hpp"
#include "WinUser.h"

PIXELFORMATDESCRIPTOR MainWnd::pfd = {
	sizeof(PIXELFORMATDESCRIPTOR),	// 像素描述结构的大小 
	1,								// 版本号
	PFD_DRAW_TO_WINDOW |			// 缓存区的输出显示在一个窗口中
	PFD_SUPPORT_OPENGL |			// 缓存区支持OpenGL绘图
	PFD_STEREO |					// 颜色缓存区是立体缓存
	PFD_DOUBLEBUFFER,				// 颜色缓存区是双缓存
	PFD_TYPE_RGBA,					// 使用RGBA颜色格式
	16,								// 颜色缓存区中颜色值所占的位深
	0, 0, 0, 0, 0, 0,				// 使用默认的颜色设置
	0,								// 无Alpha缓存
	0,								// 颜色缓存区中alpha成分的移位计数
	0,								// 无累计缓存区
	0, 0, 0, 0,						// 累计缓存区无移位
	32,								// 32位深度缓存
	0,								// 无蒙版缓存
	0,								// 无辅助缓存区
	PFD_MAIN_PLANE,					// 必须为PFD_MAIN_PLANE，设置为主绘图层
	0,								// 表示OpenGL实现所支持的上层或下层平面的数量
	0, 0, 0							// 过时，已不再使用
};

bool MainWnd::changeScreenSetting()
{
	DEVMODE dmScreenSettings;									// 设备模式
	ZeroMemory(&dmScreenSettings, sizeof(DEVMODE));				// 清零结构
	dmScreenSettings.dmSize = sizeof(DEVMODE);					// 结构大小
	dmScreenSettings.dmPelsWidth = getWidth();					// 设置宽度
	dmScreenSettings.dmPelsHeight = getHight();					// 设置高度
	dmScreenSettings.dmBitsPerPel = bitsDepth;					// 设置位深度																	                     
	dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	return ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL;
}

LRESULT MainWnd::mainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

void MainWnd::create()
{
	int x0 = 0, y0 = 0;
	RECT windowRect = { getX0(), getY0(), getX0() + getWidth(), getY0() + getHight() };
	if (isFullScreen())
	{
		if (changeScreenSetting())
		{
			ShowCursor(false);
			style  = WS_POPUP;				// 设置窗口模式为顶层窗口
			eStyle |= WS_EX_TOPMOST;
		}
		else
		{
			setFullScreen(false);
			MessageBox(HWND_DESKTOP, L"显示模式转换失败！", L"Error", MB_OK | MB_ICONEXCLAMATION);
		}
	}
	else
	{
		eStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// 使窗口具有3D外观
		x0 = (GetSystemMetrics(SM_CXSCREEN) - getWidth()) / 2;  // 计算窗口居中用
		y0 = (GetSystemMetrics(SM_CYSCREEN) - getHight()) / 2;

		AdjustWindowRectEx(&windowRect, style, 0, eStyle);		
		if (windowRect.left < 0)						// 如果窗口X坐标为负，移动坐标到0处，并调整窗口的位置
		{
			windowRect.right -= windowRect.left;
			windowRect.left = 0;
		}
		if (windowRect.top < 0)							// 如果窗口Y坐标为负，移动坐标到0处，并调整窗口的位置
		{
			windowRect.bottom -= windowRect.top;
			windowRect.top = 0;
		}
	}

	int w = windowRect.right - windowRect.left;
	int h = windowRect.bottom - windowRect.top;
	m_hWnd = CreateWindowEx(eStyle,	className, title, style, x0, y0, w, h, HWND_DESKTOP, 0, instance, lpParam);

	ShowWindow(m_hWnd, SW_NORMAL);
}

void MainWnd::setFullScreen(bool f)
{

}

void MainWnd::onKeyDown(UINT keyID)
{
	if (keyID == VK_F1)
	{
		if (isFullScreen())
		{
			
			SetWindowLong(m_hWnd, GWL_STYLE, WS_TILEDWINDOW);
			SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 1024, 768, SWP_SHOWWINDOW);
			setFullScreen(false);
		}
		else
		{
			setFullScreen();
			HWND hDesk;
			RECT rc;
			hDesk = GetDesktopWindow();
			GetWindowRect(hDesk, &rc);
			SetWindowLong(m_hWnd, GWL_STYLE, WS_BORDER);
			SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, rc.right, rc.bottom, SWP_SHOWWINDOW);
		}	
	}

}