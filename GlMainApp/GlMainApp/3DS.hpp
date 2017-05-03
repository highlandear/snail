#pragma once
#include <string>
#include <vector>
#include "vector3D.hpp"
/**
	3DS 格式文件解析相关
	
*/

// 文件开始的Primary Chunk
#define MAIN3DS       0x4D4D

// 主块(Main Chunks)
#define OBJECTINFO    0x3D3D		// 网格对象的版本号
#define VERSION       0x0002		// 3ds文件的版本
#define EDITKEYFRAME  0xB000		// 所有关键帧信息的头部

// 对象的次级定义
#define EDIT_MATERIAL 0xAFFF		// 纹理信息
#define EDIT_OBJECT	  0x4000		// 对象的面、顶点等信息

#define MESH_VERSION  0x3D3E

// 材质的次级定义
#define MATNAME       0xA000		// 材质名称
#define MATDIFFUSE    0xA020		// 对象/材质的颜色
#define COLOR_24	  0x0011
#define MATMAP        0xA200		// 新材质的头部
#define MATMAPFILE    0xA300		// 保存纹理的文件名
#define OBJ_MESH	  0x4100		// 新的网格对象

// 网格对象的次级定义
#define OBJ_VERTICES  0x4110		// 对象顶点
#define OBJ_FACES	  0x4120		// 对象的面
#define OBJ_MATERIAL  0x4130		// 对象的材质
#define OBJ_UV		  0x4140		// 对象的UV纹理坐标
#define OBJ_SMOOTH	  0x4150
#define MESH_MATRIX	  0x4160

typedef unsigned short TDSWORD;
typedef unsigned int  TDSDWORD;
typedef unsigned char TDSBYTE;

typedef struct _Chunk
{
	TDSWORD id;
	TDSDWORD len;
}TDSChunk;

typedef struct _3DSFace
{
	unsigned short vertex_index[3];
	unsigned short coord_index[3];
}TDSFace;

typedef struct _3DSObject
{
	std::string name;
	std::vector<Vector3D> vertices;
	std::vector<Vector2D> texuvs;
	std::vector<TDSFace> faces;
}TDSObject;

typedef struct _3DSMaterial
{
	std::string name;
	std::string filename;
	TDSBYTE  color[3];
}TDSMaterial;

typedef struct _3DSModel
{
	std::vector<TDSObject> objs;
	std::vector<TDSMaterial> mats;
}TDSModel;

class TDSFile
{
public:
	bool load(std::wstring pn);
	bool readChunkHead(TDSChunk & chunk);

	void read3DS(int len);
	void readObject(int len);
	void readMaterial(int len);
	void readObjMesh(int len, TDSObject & tdsobj);
	void readObjVertex(int len, TDSObject & tdsobj);
	void readObjFace(int len, TDSObject & tdsobj);
	void readObjUV(int len, TDSObject & tdsobj);
	
	void readObjMat(int len);
	void readMatColor(int len, TDSMaterial & tdsmat);
	void readMatMap(int len, TDSMaterial & tdsmat);


	size_t readString(char * out);
private:
	FILE * m_File;

	TDSModel m_Model;
};