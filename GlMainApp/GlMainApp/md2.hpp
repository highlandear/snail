#pragma once
#include "3dmodel.hpp"

struct tMd2Header
{
	int magic;					// �ļ���־
	int version;				// �ļ��汾��
	int skinWidth;				// ������
	int skinHeight;				// ����߶�
	int frameSize;				// ÿһ֡���ֽ���
	int numSkins;				// ������Ŀ
	int numVertices;			// ������Ŀ(ÿһ֡��)
	int numTexCoords;			// ����������Ŀ
	int numTriangles;			// ��������Ŀ
	int numGlCommands;			// gl������Ŀ
	int numFrames;				// ��֡��
	int offsetSkins;			// �����ƫ��λ��
	int offsetTexCoords;		// ���������ƫ��λ��
	int offsetTriangles;		// ������������ƫ��λ��
	int offsetFrames;			// ��һ֡��ƫ��λ��
	int offsetGlCommands;		// OPenGL�����ƫ��λ��
	int offsetEnd;				// �ļ���βƫ��λ��
};

class MD2File
{
public:
	bool load(std::wstring pn);
	void draw() { m_Model.draw(); }
	void init() { m_Model.init(); }

private:


	FILE * m_File;

	TModel m_Model;
};