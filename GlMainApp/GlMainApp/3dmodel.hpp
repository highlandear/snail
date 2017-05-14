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
	�������������Ϣ
*/
typedef struct _ModelObject
{
	std::string name;
	std::vector<Vector3D> vertices;	// ģ���ж�������ж���
	std::vector<ModelFace> faces;		// ģ���ж������������Ϣ����Ҫ�Ƕ����������
	std::vector<Vector2D> texuvs;	// ����UV
	std::string texname;			// ����ID, mats�еĵڼ���
	int texindex;

}MObject;

/*
	ģ�����������Ϣ
*/
typedef struct _ModelMaterial
{
	std::string name;				// ��������
	std::string filename;			// ���������ļ�������
	TDSBYTE  color[3];				// �����RGB��ɫ
//	int tid;						// ����ID
}MMaterial;


typedef struct _3DModel
{
	void drawHollow();

	void draw();

	void init();

	void loadTex();

	std::vector<MObject> objs;	// ģ�ͷֿ����ļ���
	std::vector<MMaterial> mats;	// ģ�Ͳ��ʵļ���
}TModel;

