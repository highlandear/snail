#pragma once
//#include <windows.h>
#include "camera.hpp"
class World
{
public:
	World () : cam(Camera(Pos(0.5, 0.5, 0.5))) {}
	bool init(HDC & h);
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
};

class WorldManager
{
public:
	static World & getWorld() { return wd; }

private:
	static World wd;
};
