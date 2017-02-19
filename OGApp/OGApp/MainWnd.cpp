#include "MainWnd.hpp"

bool MainWnd::changeScreenSetting()
{
	DEVMODE dmScreenSettings;									// �豸ģʽ
	ZeroMemory(&dmScreenSettings, sizeof(DEVMODE));				// ����ṹ
	dmScreenSettings.dmSize = sizeof(DEVMODE);					// �ṹ��С
	dmScreenSettings.dmPelsWidth = getWidth();					// ���ÿ��
	dmScreenSettings.dmPelsHeight = getHight();					// ���ø߶�
	dmScreenSettings.dmBitsPerPel = bitsDepth;					// ����λ���
																	                     
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
			style  = WS_POPUP;				// ���ô���ģʽΪ���㴰��
			eStyle |= WS_EX_TOPMOST;
		}
		else
		{
			setFullScreen(false);
			MessageBox(HWND_DESKTOP, L"��ʾģʽת��ʧ�ܣ�", L"Error", MB_OK | MB_ICONEXCLAMATION);
		}
	}
	else
	{
		eStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// ʹ���ھ���3D���
		x0 = (GetSystemMetrics(SM_CXSCREEN) - getWidth()) / 2;  // ���㴰�ھ�����
		y0 = (GetSystemMetrics(SM_CYSCREEN) - getHight()) / 2;

		//AdjustWindowRectEx(&windowRect, style, 0, eStyle);
		
		if (windowRect.left < 0)						// �������X����Ϊ�����ƶ����굽0�������������ڵ�λ��
		{
			windowRect.right -= windowRect.left;
			windowRect.left = 0;
		}
		if (windowRect.top < 0)							// �������Y����Ϊ�����ƶ����굽0�������������ڵ�λ��
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