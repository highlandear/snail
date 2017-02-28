#pragma once



namespace gdraw
{
	void drawBall(float radius);
	

	void drawBall(float radius, float x, float y, float z);
	

	void drawCube(float size);
	

	void drawCube(float size, float x, float y, float z);
	
	void drawTeaPot(float size);

	void drawTeaPot(float size, float x, float y, float z);

	void print(float x, float y, float z, const char * str);

	void wprint(float x, float y, float z, const wchar_t *str);
	
}