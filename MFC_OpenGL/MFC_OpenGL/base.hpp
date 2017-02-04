#pragma once

#define sz(n) (sizeof(n)/sizeof(n[0]))

class Base
{
public:
	virtual void show() = 0;
};

class Cube : public Base
{
public:
	virtual void show();
	Cube(float s) { sizef = s; }
	Cube() { sizef = 1.0f; }
	void operator ()() {};

private:
	float sizef;
};

class Pot : public Base
{
public:
	virtual void show();

	Pot(float s) : sizef(s){}
	Pot() { sizef = 0.5f; }
	void operator ()() { };

private:
	float sizef;
};

class Coord : public Base
{
public:
	virtual void show();

	static void globalshow();

	Coord(){ x0 = y0 = z0 = 0.0f; sizef = 0.8; }
	Coord(float x, float y, float z, float s) :x0(x), y0(y), z0(z), sizef(s){}

	void operator()(){}

private:
	float x0, y0, z0, sizef;
};
