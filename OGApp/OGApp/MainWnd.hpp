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
			sizeof(PIXELFORMATDESCRIPTOR),					// 像素描述结构的大小 
			1,												// 版本号
			PFD_DRAW_TO_WINDOW |							// 缓存区的输出显示在一个窗口中
			PFD_SUPPORT_OPENGL |							// 缓存区支持OpenGL绘图
			PFD_STEREO |									// 颜色缓存区是立体缓存
			PFD_DOUBLEBUFFER,								// 颜色缓存区是双缓存
			PFD_TYPE_RGBA,									// 使用RGBA颜色格式
			(BYTE)b,									// 颜色缓存区中颜色值所占的位深
			0, 0, 0, 0, 0, 0,								// 使用默认的颜色设置
			0,												// 无Alpha缓存
			0,												// 颜色缓存区中alpha成分的移位计数
			0,												// 无累计缓存区
			0, 0, 0, 0,										// 累计缓存区无移位
			32,												// 32位深度缓存
			0,												// 无蒙版缓存
			0,												// 无辅助缓存区
			PFD_MAIN_PLANE,									// 必须为PFD_MAIN_PLANE，设置为主绘图层
			0,												// 表示OpenGL实现所支持的上层或下层平面的数量
			0, 0, 0											// 过时，已不再使用
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
	PIXELFORMATDESCRIPTOR pfd;

};