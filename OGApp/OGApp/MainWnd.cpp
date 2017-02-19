#include "MainWnd.hpp"

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

		//AdjustWindowRectEx(&windowRect, style, 0, eStyle);
		
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