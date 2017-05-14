#pragma once
#include <string>
#include <vector>
#include "vector3D.hpp"

typedef unsigned short TDSWORD;
typedef unsigned int  TDSDWORD;
typedef unsigned char TDSBYTE;

typedef struct _ModelFace
{
	unsigned short vertex_index[3];
	unsigned short coord_index[3];
}ModelFace;

/*
	对象网格相关信息
*/
typedef struct _ModelObject
{
	std::string name;
	std::vector<Vector3D> vertices;	// 模型中对象的所有顶点
	std::vector<ModelFace> faces;		// 模型中对象的面描述信息（主要是顶点的索引）
	std::vector<Vector2D> texuvs;	// 纹理UV
	std::string texname;			// 材质ID, mats中的第几个
	int texindex;

}MObject;

/*
	模型纹理材质信息
*/
typedef struct _ModelMaterial
{
	std::string name;				// 纹理名称
	std::string filename;			// 纹理所在文件的名称
	TDSBYTE  color[3];				// 对象的RGB颜色
//	int tid;						// 纹理ID
}MMaterial;


typedef struct _3DModel
{
	void drawHollow();

	void draw();

	void init();

	void loadTex();

	std::vector<MObject> objs;	// 模型分块对象的集合
	std::vector<MMaterial> mats;	// 模型材质的集合
}TModel;

