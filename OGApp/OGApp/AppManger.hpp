#pragma once
#include <windows.h> 
#include "MainWnd.hpp"

class AppManger
{
public:
	AppManger(MainWnd * w)
	{
		m = w;
	}

	void showDialog();

	static LRESULT CALLBACK DlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

	static void setMainWnd(MainWnd * w) { m = w; }
	static MainWnd * getMainWnd() { return m; }

private:
	static MainWnd * m;
};