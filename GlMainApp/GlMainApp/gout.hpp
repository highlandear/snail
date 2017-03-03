#pragma once
#include <string>
#include <vector>
#include <windows.h>

/**
	�ַ��������������һЩ����
*/
class gout
{
public :
	template <typename T>
	static std::wstring toString(T t);

	static std::wstring wstringPos(float x, float y, float z);

	static std::wstring wstringPos(float x, float y);

	static void split(std::wstring str, std::vector<std::wstring> & v, std::wstring sep = L" ");

	
	static void wprint(std::wstring str, float x, float y, float z);

	static void wprint3D(std::wstring, float x, float y, float z, float d);

	static bool isExtSupported(const char * ext);

private:

	static void xprint(std::wstring str, float x, float y, float z);
	
	static HFONT sFont;

	static int fontSize;
};