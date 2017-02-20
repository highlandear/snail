#pragma once
#include <windows.h>

class MainWnd
{
public:
	void onKeyDown(UINT keyID);
	void create();
	bool changeScreenSetting();

	MainWnd(HINSTANCE i, LPCWSTR t, LPCWSTR c) : instance(i), title(t), className(c), bitsDepth(16), fscreen(false)
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
	}
	
	inline int getWidth() { return fscreen ? screen_w : window_w; }
	inline int getHight() { return fscreen ? screen_h : window_h; }
	inline void setWidth(int w) { fscreen ? screen_w = w : window_w = w; }
	inline void setHight(int h) { fscreen ? screen_h = h : window_h = h; }
	inline int getX0() { return fscreen ?  0 : upleft_x; }
	inline int getY0() { return fscreen ?  0 : upleft_y; }
	inline void setX0(int x) { upleft_x = x; }
	inline void setY0(int y) { upleft_y = y; }
	inline bool isFullScreen() { return fscreen; }
	void setFullScreen(bool f = true);
	inline void setColor_16() { bitsDepth = 16; }
	inline void setColor_32() { bitsDepth = 32; }
	inline int geColorBits() { return bitsDepth; }

	HWND getHwnd() { return m_hWnd; }

	static LRESULT CALLBACK mainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:						// out
	HWND	m_hWnd;				// window handle
	HDC		m_hDC;				// 
	HGLRC	m_hRC;
	
private:						// in 
	HINSTANCE	instance;
	LPCWSTR		title;			
	LPCWSTR		className;
	DWORD		style;			// 定义我们窗口类型，使用常规设定
	DWORD		eStyle;
	int			bitsDepth;		// 颜色位深
	bool		fscreen;		// 是否全屏
	LPVOID		lpParam;		//

private:
	int		upleft_x;				// 窗口的左上角的X位置 
	int		upleft_y;				// 窗口的左上角的Y位置 
	int		window_w;				// 窗口的宽度
	int		window_h;				// 窗口的高度
	int		screen_w;				// 全屏的宽度
	int		screen_h;				// 全屏的高度

private:
	static PIXELFORMATDESCRIPTOR pfd;

};