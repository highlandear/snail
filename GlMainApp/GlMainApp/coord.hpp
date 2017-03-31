#pragma once

class Coord
{
public:
	virtual void draw();

	static void globalshow();

	Coord() { x0 = y0 = z0 = 0.0f; sizef = 0.8; }
	Coord(float x, float y, float z, float s) :x0(x), y0(y), z0(z), sizef(s) {}

	//void operator()() {}

	void setSizef(float sz) { sizef = sz; }
private:
	float x0, y0, z0, sizef;
};