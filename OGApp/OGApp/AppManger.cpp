
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
			{
				m->setFullScreen();
				MessageBox(hwndDlg, L"full", L"tip", MB_OK);

			}
			else
				MessageBox(hwndDlg,  L"window", L"tip", MB_OK);
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