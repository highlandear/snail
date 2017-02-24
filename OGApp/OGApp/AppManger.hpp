#pragma once
#include <windows.h> 
#include "MainWnd.hpp"
#include "GLEnv.hpp"

class Setting
{
	enum enumSetting { eBitDepth, eFullScreen, eWidth, eHight, eMAX };
public:
	void setColor_16() { set(eBitDepth, 16); }
	void setColor_32() { set(eBitDepth, 32); }
	int getColor() { return get(eBitDepth); }
	void setFullScreen(bool t = false) { set(eFullScreen, t ? 1 : 0); }
	bool isFull() { return 1 == get(eFullScreen); }
	void setWidth(int w) { set(eWidth, w); }
	void setHight(int h) { set(eHight, h); }
	int getWidth() { return get(eWidth); }
	int getHight() { return get(eHight); }

private:
	inline void set(enumSetting e, int v) { settings[e] = v; }
	inline int get(enumSetting e) { return settings[e]; }

	int settings[eMAX];
};

class AppManger
{

public:

	AppManger(MainWnd * w) { m_Pwnd = w; }

	void showDialog();

	static LRESULT CALLBACK DlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

	static MainWnd * getMainWnd() { return m_Pwnd; }

	static void startTimer(UINT i, UINT e);
	
	static void CALLBACK TimerProc(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime);

private:

	static Setting config;

	static MainWnd * m_Pwnd;	
};