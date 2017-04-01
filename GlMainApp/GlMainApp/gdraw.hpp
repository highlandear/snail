#pragma once
#include <windows.h>

/**
	һЩ��׼����Ļ���
*/
namespace gdraw
{
	void drawBall(float radius);	

	void drawBall(float radius, float x, float y, float z);	

	void drawCube(float size);	

	void drawCube(float x, float y, float z, float size);
	
	void drawTeaPot(float size);

	void drawTeaPot(float size, float x, float y, float z);
	
	void drawGrid(float field, float interval);

	void drawCube();
};
