#pragma once
#include <string>
#include <vector>
#include "vector3D.hpp"
/**
	3DS ��ʽ�ļ��������
	
*/

// �ļ���ʼ��Primary Chunk
#define MAIN3DS       0x4D4D

// ����(Main Chunks)
#define OBJECTINFO    0x3D3D		// �������İ汾��
#define VERSION       0x0002		// 3ds�ļ��İ汾
#define EDITKEYFRAME  0xB000		// ���йؼ�֡��Ϣ��ͷ��

// ����Ĵμ�����
#define EDIT_MATERIAL 0xAFFF		// ������Ϣ
#define EDIT_OBJECT	  0x4000		// ������桢�������Ϣ

#define MESH_VERSION  0x3D3E

// ���ʵĴμ�����
#define MATNAME       0xA000		// ��������
#define MATDIFFUSE    0xA020		// ����/���ʵ���ɫ
#define COLOR_24	  0x0011
#define MATMAP        0xA200		// �²��ʵ�ͷ��
#define MATMAPFILE    0xA300		// ����������ļ���
#define OBJ_MESH	  0x4100		// �µ��������

// �������Ĵμ�����
#define OBJ_VERTICES  0x4110		// ���󶥵�
#define OBJ_FACES	  0x4120		// �������
#define OBJ_MATERIAL  0x4130		// ����Ĳ���
#define OBJ_UV		  0x4140		// �����UV��������
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