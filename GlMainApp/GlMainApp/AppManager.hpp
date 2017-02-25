#pragma once
#include <windows.h> 
#include "MainWnd.hpp"
#include "GLEnv.hpp"


class AppManager
{

public:

	AppManager(MainWnd * w) { pWnd = w; }

	static MainWnd * getMainWnd() { return pWnd; }

private:

	static MainWnd * pWnd;	
};