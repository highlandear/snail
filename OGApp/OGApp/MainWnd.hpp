#pragma once
#include <windows.h>

class MainWnd
{
public:
	void create();
	bool changeScreenSetting();

	MainWnd(HINSTANCE i, LPCWSTR t, LPCWSTR c, int b, bool f) : instance(i), title(t), className(c), bitsDepth(b), fscreen(f)
	{ 
		upleft_x = 0;
		upleft_y = 0;
		window_w = 640;
		window_h = 480;

		screen_w = 1024;
		screen_h = 768;

		m_hDC = 0;
		m_hRC = 0;
		m_hWnd = 0;

		style = WS_TILEDWINDOW;
		eStyle = WS_EX_APPWINDOW;

		pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),					// ���������ṹ�Ĵ�С 
			1,												// �汾��
			PFD_DRAW_TO_WINDOW |							// �������������ʾ��һ��������
			PFD_SUPPORT_OPENGL |							// ������֧��OpenGL��ͼ
			PFD_STEREO |									// ��ɫ�����������建��
			PFD_DOUBLEBUFFER,								// ��ɫ��������˫����
			PFD_TYPE_RGBA,									// ʹ��RGBA��ɫ��ʽ
			(BYTE)b,									// ��ɫ����������ɫֵ��ռ��λ��
			0, 0, 0, 0, 0, 0,								// ʹ��Ĭ�ϵ���ɫ����
			0,												// ��Alpha����
			0,												// ��ɫ��������alpha�ɷֵ���λ����
			0,												// ���ۼƻ�����
			0, 0, 0, 0,										// �ۼƻ���������λ
			32,												// 32λ��Ȼ���
			0,												// ���ɰ滺��
			0,												// �޸���������
			PFD_MAIN_PLANE,									// ����ΪPFD_MAIN_PLANE������Ϊ����ͼ��
			0,												// ��ʾOpenGLʵ����֧�ֵ��ϲ���²�ƽ�������
			0, 0, 0											// ��ʱ���Ѳ���ʹ��
		};
	}
	
	inline int getWidth() { return fscreen ? screen_w : window_w; }
	inline int getHight() { return fscreen ? screen_h : window_h; }
	inline void setWidth(int w) { fscreen ? screen_w = w : window_w = w; }
	inline void setHight(int h) { fscreen ? screen_h = h : window_h = h; }

	inline void setFullScreen(bool f = true) { fscreen = f; }
	inline bool isFullScreen() { return fscreen; }
	inline int getX0() { return fscreen ?  0 : upleft_x; }
	inline int getY0() { return fscreen ?  0 : upleft_y; }
	inline void setX0(int x) { upleft_x = x; }
	inline void setY0(int y) { upleft_y = y; }

	HWND getHwnd() { return m_hWnd; }

private:						// out
	HWND	m_hWnd;				// window handle
	HDC		m_hDC;				// 
	HGLRC	m_hRC;
	
private:						// in 
	HINSTANCE	instance;
	LPCWSTR		title;			
	LPCWSTR		className;
	DWORD		style;			// �������Ǵ������ͣ�ʹ�ó����趨
	DWORD		eStyle;
	int			bitsDepth;		// ��ɫλ��
	bool		fscreen;		// �Ƿ�ȫ��
	LPVOID		lpParam;		//

private:
	int		upleft_x;				// ���ڵ����Ͻǵ�Xλ�� 
	int		upleft_y;				// ���ڵ����Ͻǵ�Yλ�� 
	int		window_w;				// ���ڵĿ��
	int		window_h;				// ���ڵĸ߶�
	int		screen_w;				// ȫ���Ŀ��
	int		screen_h;				// ȫ���ĸ߶�

private:
	PIXELFORMATDESCRIPTOR pfd;

};