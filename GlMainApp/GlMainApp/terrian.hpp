#pragma once
#include "tex.hpp"

class Terrain
{
public:

	Terrain(std::wstring hmpn, int w, int h, int s); 
	Terrain() { m_pData = NULL; }

	~Terrain() { _SAFE_DEL_ARRAY(m_pData); }

	bool load();

	void init();

	void setTexName(std::wstring n) { m_szTexName = n; }

	/*
		 获取网格 (row, col)的高度值
	*/
	int find(int row, int col);

	/*
		根据 x - z平面上的坐标，获取坐标 y 的高度值
	*/
	int getAveHeight(float x, float z);


	void draw();

	/*
		高度图中的0 - 255 和坐标高度的对应关系
	*/
	float floatHeight(unsigned char v) { return (float)v; }

	void drawGrid();

	void drawPoints();

	void drawGridPoints();

	void drawSign();

	void setTexCoord(float x, float z);

private:
	std::wstring m_szHeightMapName; // 地表高度描述文件
	std::wstring m_szTexName;		// 地表纹理

	int m_width;					// 网格 X方向上的顶点数
	int m_height;					// 网格 Z方向上的顶点数
	int m_scale;					// 每一格宽度

	unsigned char * m_pData;        // 存放高度信息

};
