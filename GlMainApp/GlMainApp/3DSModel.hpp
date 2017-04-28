#pragma once
#include "3DS.hpp"
#include <string>
#include <vector>

typedef struct _Face
{
	int vertIndex[3];		// ��������
	int coordIndex[3];		// ������������
}TDSFace;


typedef struct _MatInfo
{
	char  strName[255];			   // ��������
	char  strFile[255];			   // �����ļ�����
	unsigned char color[3];		   // �����RGB��ɫ
	int   texureId;				   // ����ID
	float uTile;				   // u �ظ�
	float vTile;				   // v �ظ�
	float uOffset;			       // u ����ƫ��
	float vOffset;				   // v ����ƫ��
}TDSMatInfo;

/** ������Ϣ�ṹ�� */
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
