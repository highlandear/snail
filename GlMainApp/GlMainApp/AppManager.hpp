#pragma once
#include <windows.h> 
#include "MainWnd.hpp"
#include "GLEnv.hpp"


class AppManager
{

public:

	AppManager(MainWnd * w) { pWnd = w;}

	static MainWnd * getMainWnd() { return pWnd; }

	UINT setTimer(UINT id, UINT eclapse = 50);

private:

	static void AppManager::TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

	static MainWnd * pWnd;	
};