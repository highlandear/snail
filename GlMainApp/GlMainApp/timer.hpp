#pragma once
#include <windows.h>

namespace helper
{
	/*
		ʱ�����������ǰʱ����ϴ�ʱ��������e ,���ӵ�ǰʱ�䣬Ҫô�ͷ��� 0
	*/
	DWORD getElapse(DWORD e)
	{
		static DWORD lastT = 0;

		DWORD curT =  GetTickCount();

		return ((curT - lastT) > e) ?  lastT = curT : 0;
	}
}
