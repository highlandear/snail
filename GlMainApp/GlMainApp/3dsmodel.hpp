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
	std::vector<Vector3D> vertices;	// ģ���ж�������ж���
	std::vector<TDSFace> faces;		// ģ���ж������������Ϣ����Ҫ�Ƕ����������
	std::vector<Vector2D> texuvs;	// ����UV
	std::string texname;			// ����ID, mats�еĵڼ���
	int texindex;

}TDSObject;

typedef struct _3DSMaterial
{
	std::string name;				// ��������
	std::string filename;			// ���������ļ�������
	TDSBYTE  color[3];				// �����RGB��ɫ
	int tid;						// ����ID
}TDSMaterial;

typedef struct _3DSModel
{
	void drawHollow();

	void draw();

	void init();

	void loadTex();

	std::vector<TDSObject> objs;	// ģ�ͷֿ����ļ���
	std::vector<TDSMaterial> mats;	// ģ�Ͳ��ʵļ���
}TDSModel;

