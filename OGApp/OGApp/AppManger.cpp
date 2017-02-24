
#include "Resource.h"
#include "AppManger.hpp"

MainWnd* AppManger::m_Pwnd;
Setting AppManger::config;

void AppManger::showDialog()
{
	DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_CONF), HWND_DESKTOP, (DLGPROC)DlgProc);
}

LRESULT AppManger::DlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			if (IsDlgButtonChecked(hwndDlg, IDC_FULLSCREEN))
				config.setFullScreen();
			else
				config.setFullScreen(false);

			if (IsDlgButtonChecked(hwndDlg, IDC_16BPP))
				config.setColor_16();

			else if (IsDlgButtonChecked(hwndDlg, IDC_32BPP))
				config.setColor_32();

			if (IsDlgButtonChecked(hwndDlg, IDC_640_480))
			{
				config.setWidth(640); config.setHight(480);
			}
			else if (IsDlgButtonChecked(hwndDlg, IDC_800_600))
			{
				config.setWidth(800); config.setHight(600);
			}
			else if (IsDlgButtonChecked(hwndDlg, IDC_1024_768))
			{
				config.setWidth(1024); config.setHight(768);
			}

			EndDialog(hwndDlg, false);
			m_Pwnd->create(config.getColor(), config.isFull(), config.getWidth(), config.getHight());
			
			startTimer(1, 10);

			return TRUE;
		}
		case IDCANCEL:
		{
			EndDialog(hwndDlg, false);
			PostQuitMessage(0);
			return TRUE;
		}
		break;

		default:
			break;
		}
		switch (HIWORD(wParam))
		{
			case BN_CLICKED:
				CheckDlgButton(hwndDlg, lParam, BST_CHECKED);
			break;
		}
	}break;
	case WM_CLOSE:
	{
		EndDialog(hwndDlg, false);
		PostQuitMessage(0);
	}break;
	case WM_INITDIALOG:
	{
		CheckDlgButton(hwndDlg, IDC_FULLSCREEN, BST_UNCHECKED);    
		CheckRadioButton(hwndDlg, IDC_640_480, IDC_1024_768, IDC_640_480);
		CheckRadioButton(hwndDlg, IDC_16BPP, IDC_32BPP, IDC_32BPP);
	}

	default:
		break;
	}
	return FALSE;
}

void AppManger::startTimer(UINT i, UINT e)
{
	if (NULL == m_Pwnd->getHwnd())
		return;

	SetTimer(m_Pwnd->getHwnd(), i, e, (TIMERPROC)AppManger::TimerProc);
}

void AppManger::TimerProc(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime)
{
	if (iTimerID == 1)
	{
		m_Pwnd->maindraw();
	}

}