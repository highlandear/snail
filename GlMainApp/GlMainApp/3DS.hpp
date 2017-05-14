#pragma once

/*
	.3DS ��ʽ�ļ��������
*/

#include"3dfile.hpp"

#define ID_3DS_MAIN     0x4D4D		// 3DS �ļ��ı�ʶ��  0x4D4D
#define ID_3DS_OBJ		0x3D3D		// �������İ汾��
#define ID_3DS_VER		0x0002		// 3ds�ļ��İ汾
#define ID_3DS_KEYFRAME	0xB000		// ���йؼ�֡��Ϣ��ͷ��
									// ����Ĵμ�����
#define ID_OBJ_MAT		0xAFFF		// ������Ϣ
#define ID_OBJ_INFO		0x4000		// ������桢�������Ϣ
#define ID_OBJ_MESHVER  0x3D3E		// ��������汾
									// ���ʵĴμ�����
#define ID_MAT_NAME		0xA000		// ��������
#define ID_MAT_COLOR	0xA020		// ����/���ʵ���ɫ
#define ID_MAT_MAP      0xA200		// �²��ʵ�ͷ��
#define ID_COLOR_24		0x0011		// ������ɫ�Ĵμ�����

#define ID_MAP_FILE		0xA300		// ����������ļ���
#define ID_INFO_MESH	0x4100		// �µ��������
									// �������Ĵμ�����
#define ID_MESH_VERTICES  0x4110	// ���󶥵�
#define ID_MESH_FACES	  0x4120	// �������
#define ID_MESH_MAT		  0x4130	// ����Ĳ���
#define ID_MESH_TEX		  0x4140	// �����UV��������
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