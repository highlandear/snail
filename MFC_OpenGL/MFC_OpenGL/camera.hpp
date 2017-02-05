#pragma once
#include "stdafx.h"
#include "pos.hpp"

class Camera
{
public:
	void set() const;
	
	Camera(Pos& s0, Pos& f0, Dir& v0) : p(s0), f(f0), v(v0)  {}

	Camera(Pos& s0, Pos& f0) :p(s0), f(f0), v(Dir(0.0f, 1.0f, 0.0f)) {}

	Camera(Pos& s0):p(s0), f(Pos(0.0f, 0.0f, 0.0f)), v(Dir(0.0f, 1.0f, 0.0f)) {}

	Camera() {}


private:
	Pos p;
	Pos f;
	Dir v;
};

