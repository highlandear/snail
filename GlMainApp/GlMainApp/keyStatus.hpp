#pragma once
#include <windows.h>

#define KEY_NUM 256

class KeyStatus
{

public:
	static void setKeyDown(UINT k) { keys[k] = true; }
	static void setKeyUp(UINT k) { keys[k] = false; }
	static bool isKeyDown(UINT k) { return keys[k]; }
private:
	static bool keys[KEY_NUM];
};
