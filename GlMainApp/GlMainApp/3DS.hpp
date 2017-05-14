#pragma once

/*
	.3DS 格式文件解析相关
*/

#include"3dfile.hpp"

#define ID_3DS_MAIN     0x4D4D		// 3DS 文件的标识是  0x4D4D
#define ID_3DS_OBJ		0x3D3D		// 网格对象的版本号
#define ID_3DS_VER		0x0002		// 3ds文件的版本
#define ID_3DS_KEYFRAME	0xB000		// 所有关键帧信息的头部
									// 对象的次级定义
#define ID_OBJ_MAT		0xAFFF		// 纹理信息
#define ID_OBJ_INFO		0x4000		// 对象的面、顶点等信息
#define ID_OBJ_MESHVER  0x3D3E		// 对象网格版本
									// 材质的次级定义
#define ID_MAT_NAME		0xA000		// 材质名称
#define ID_MAT_COLOR	0xA020		// 对象/材质的颜色
#define ID_MAT_MAP      0xA200		// 新材质的头部
#define ID_COLOR_24		0x0011		// 材质颜色的次级定义

#define ID_MAP_FILE		0xA300		// 保存纹理的文件名
#define ID_INFO_MESH	0x4100		// 新的网格对象
									// 网格对象的次级定义
#define ID_MESH_VERTICES  0x4110	// 对象顶点
#define ID_MESH_FACES	  0x4120	// 对象的面
#define ID_MESH_MAT		  0x4130	// 对象的材质
#define ID_MESH_TEX		  0x4140	// 对象的UV纹理坐标
#define ID_MESH_SMOOTH	  0x4150
#define ID_MESH_MATRIX	  0x4160


typedef struct _Chunk
{
	TDSWORD id;
	TDSDWORD len;
}TDSChunk;


class TDSFile : public ModelFile
{
public:
	bool load(std::wstring pn);

	void init() { m_Model.init(); }

	void draw() { m_Model.draw(); }
private:

	bool readChunkHead(TDSChunk & chunk);
	void read3DS(int len);
	void readObject(int len);
	void readMaterial(int len);
	void readObjMesh(int len, MObject & tdsobj);
	void readObjVertex(int len, MObject & tdsobj);
	void readObjFace(int len, MObject & tdsobj);
	void readObjUV(int len, MObject & tdsobj);	
	void readObjMat(int len, MObject & tdsobj);
	void readMatColor(int len, MMaterial & tdsmat);
	void readMatMap(int len, MMaterial & tdsmat);
	
	size_t readString(char * out);

	TModel m_Model;
};