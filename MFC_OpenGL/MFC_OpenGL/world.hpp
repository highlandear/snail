#pragma once
#include "camera.hpp"
class World
{
public:
	World () : cam(Camera(Pos(0.5, 0.5, 0.5))) {}
	bool init(HWND, int , int );
	void draw();
	void changeSize(int w, int h);
	void fresh();
	void call(UINT v);
	void setHdc(HDC& h) { hdc = h; }
	void setCamera(Camera& c) { cam = c; }
	Camera & getCamera() { return cam; }

private:
	Camera cam;
	HDC hdc;
	int width;
	int hight;
};

class WorldManager
{
public:
	static World & getWorld() { return wd; }

private:
	static World wd;
};
