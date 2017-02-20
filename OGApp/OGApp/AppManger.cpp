
#include "Resource.h"
#include "AppManger.hpp"

MainWnd* AppManger::m;

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
				m->setFullScreen();
			else
				m->setFullScreen(false);

			if (IsDlgButtonChecked(hwndDlg, IDC_16BPP))
				m->setColor_16();
			else if (IsDlgButtonChecked(hwndDlg, IDC_32BPP))
				m->setColor_32();

			if (IsDlgButtonChecked(hwndDlg, IDC_640_480))
			{
				m->setWidth(640); m->setHight(480);
			}
			else if (IsDlgButtonChecked(hwndDlg, IDC_800_600))
			{
				m->setWidth(800); m->setHight(600);
			}
			else if (IsDlgButtonChecked(hwndDlg, IDC_1024_768))
			{
				m->setWidth(1024); m->setHight(768);
			}

			EndDialog(hwndDlg, false);
			m->create();
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

	default:
		break;
	/*
	switch (HIWORD(wParam))
	{
	case BN_CLICKED:
		CheckDlgButton(hwndDlg, lParam, BST_CHECKED);
		break;
	}
	break;
	*/
	}
	return FALSE;
}