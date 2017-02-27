
#include "AppManager.hpp"

MainWnd* AppManager::pWnd;

UINT AppManager::setTimer(UINT id, UINT eclapse)
{
	return SetTimer(pWnd->getHwnd(), id, eclapse, (TIMERPROC)TimerProc);
}

void AppManager::TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	pWnd->maindraw();
}
