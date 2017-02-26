#pragma once
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

class Impl
{
public:
	virtual void draw() = 0;

};

class Basic : public Impl
{
public:
	void draw();
};

