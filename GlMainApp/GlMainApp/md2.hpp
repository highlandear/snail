#pragma once
#include "3dfile.hpp"
#include "animodel.hpp"

struct MD2Header
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

struct UV
{
	short u, v;
};

struct MD2Triangle
{
	float vertex[3];
	float normal[3];
};

struct FrameVertex
{
	TDSBYTE vertex[3];
	TDSBYTE lightNormalIndex;
};

// 帧结构
struct MD2Frame
{
	float scale[3];
	float translate[3];
	char name[16];
	FrameVertex fvertex[1];
};

// 关键帧
struct MD2KeyFrame
{
	std::string name;
	std::vector<MD2Triangle> triangles;
};

class MD2File : public ModelFile
{

public:

	bool load(std::wstring pn);

	void loadTex(std::string tfn);

	void draw() { m_Model.draw(); }

	void init() { m_Model.init(); };

	void update() { m_Model.update(); }

private:

	std::string readSkinName();

	int readUVs();
	int readFaces();
	int readFrames();

	void addModelAnimation();

	void addModelObjects();

	AniModel m_Model;

	MD2Header m_Header;

	std::vector<UV> m_uvs;
	std::vector<ModelFace> m_faces;
	std::vector<MD2KeyFrame> m_kfs;
};