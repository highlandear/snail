#pragma once
#include "3DS.hpp"
#include <string>
#include <vector>

typedef struct _Face
{
	int vertIndex[3];		// 顶点索引
	int coordIndex[3];		// 纹理坐标索引
}TDSFace;


typedef struct _MatInfo
{
	char  strName[255];			   // 纹理名称
	char  strFile[255];			   // 纹理文件名称
	unsigned char color[3];		   // 对象的RGB颜色
	int   texureId;				   // 纹理ID
	float uTile;				   // u 重复
	float vTile;				   // v 重复
	float uOffset;			       // u 纹理偏移
	float vOffset;				   // v 纹理偏移
}TDSMatInfo;

/** 对象信息结构体 */
typedef struct _TDSObject
{

}TDSObject;

class TDSModel
{
public:
	bool load(std::wstring pn);
	void loadObj(unsigned char * data, size_t size);
	void loadMat(unsigned char * data, size_t size);
	void init();
	void draw();
private:

	std::vector<TDSObject> objList;
	std::vector<TDSMatInfo> matList;
};
