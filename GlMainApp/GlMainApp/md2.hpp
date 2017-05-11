#pragma once
#include "3dmodel.hpp"

struct tMd2Header
{
	int magic;					// 文件标志
	int version;				// 文件版本号
	int skinWidth;				// 纹理宽度
	int skinHeight;				// 纹理高度
	int frameSize;				// 每一帧的字节数
	int numSkins;				// 纹理数目
	int numVertices;			// 顶点数目(每一帧中)
	int numTexCoords;			// 纹理坐标数目
	int numTriangles;			// 三角行数目
	int numGlCommands;			// gl命令数目
	int numFrames;				// 总帧数
	int offsetSkins;			// 纹理的偏移位置
	int offsetTexCoords;		// 纹理坐标的偏移位置
	int offsetTriangles;		// 三角形索引的偏移位置
	int offsetFrames;			// 第一帧的偏移位置
	int offsetGlCommands;		// OPenGL命令的偏移位置
	int offsetEnd;				// 文件结尾偏移位置
};

class MD2File
{
public:
	bool load(std::wstring pn);
	void draw() { m_Model.draw(); }
	void init() { m_Model.init(); }

private:


	FILE * m_File;

	TModel m_Model;
};