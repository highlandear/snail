#pragma once
namespace BOX
{
	void draw(HDC hdc);
	bool init(HDC hdc);
	void changeSize(HDC hdc, int w, int h);
	void fresh(HDC);
	void call(UINT v);

	void up(HDC);
	void down();
}
