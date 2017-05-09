#pragma once
#include <string>
#include <vector>
#include "vector3D.hpp"

typedef unsigned short TDSWORD;
typedef unsigned int  TDSDWORD;
typedef unsigned char TDSBYTE;

typedef struct _3DSFace
{
	unsigned short vertex_index[3];
	unsigned short coord_index[3];
}TDSFace;

typedef struct _3DSObject
{
	std::string name;
	std::vector<Vector3D> vertices;	// 模型中对象的所有顶点
	std::vector<TDSFace> faces;		// 模型中对象的面描述信息（主要是顶点的索引）
	std::vector<Vector2D> texuvs;	// 纹理UV
	std::string texname;			// 材质ID, mats中的第几个
	int texindex;

}TDSObject;

typedef struct _3DSMaterial
{
	std::string name;				// 纹理名称
	std::string filename;			// 纹理所在文件的名称
	TDSBYTE  color[3];				// 对象的RGB颜色
	int tid;						// 纹理ID
}TDSMaterial;

typedef struct _3DSModel
{
	void drawHollow();

	void draw();

	void init();

	void loadTex();

	std::vector<TDSObject> objs;	// 模型分块对象的集合
	std::vector<TDSMaterial> mats;	// 模型材质的集合
}TDSModel;

