#pragma once
#include <windows.h>

namespace helper
{
	/*
		时间间隔，如果当前时间比上次时间间隔大于e ,返加当前时间，要么就返回 0
	*/
	DWORD getElapse(DWORD e)
	{
		static DWORD lastT = 0;

		DWORD curT =  GetTickCount();

		return ((curT - lastT) > e) ?  lastT = curT : 0;
	}
}
