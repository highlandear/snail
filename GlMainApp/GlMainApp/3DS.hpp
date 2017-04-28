#pragma once
#include <string>

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
#define MATMAP        0xA200		// �²��ʵ�ͷ��
#define MATMAPFILE    0xA300		// ����������ļ���
#define OBJ_MESH	  0x4100		// �µ��������

// �������Ĵμ�����
#define OBJ_VERTICES  0x4110		// ���󶥵�
#define OBJ_FACES	  0x4120		// �������
#define OBJ_MATERIAL  0x4130		// ����Ĳ���
#define OBJ_UV		  0x4140		// �����UV��������
#define MESH_MATRIX	  0x4160

typedef unsigned short TDSWORD;
typedef unsigned int  TDSDWORD;
typedef unsigned char TDSBYTE;

typedef struct _Chunk
{
	TDSWORD id;
	TDSDWORD len;
//	TDSBYTE * data;

}TDSChunk;

class TDSFile
{
public:
	bool load(std::wstring pn);
	bool readChunkHead(TDSChunk & chunk);
	void read3DS(TDSDWORD len);
	void readObject(TDSDWORD len);
	void readObjMesh(TDSDWORD len);
	void readObjVertex(TDSDWORD len);
	void readObjFace(TDSDWORD len);
	void readObjUV(TDSDWORD len);
	void readObjMat(TDSDWORD len);


	size_t readString(char * out);



private:
	FILE * m_File;
	long m_cur;
};