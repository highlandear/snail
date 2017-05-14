#pragma once
#include "3dfile.hpp"
#include "animodel.hpp"

struct MD2Header
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

struct UV
{
	short u, v;
};

struct MD2Triangle
{
	float vertex[3];
	float normal[3];
};

struct FrameVertex
{
	TDSBYTE vertex[3];
	TDSBYTE lightNormalIndex;
};

// ֡�ṹ
struct MD2Frame
{
	float scale[3];
	float translate[3];
	char name[16];
	FrameVertex fvertex[1];
};

// �ؼ�֡
struct MD2KeyFrame
{
	std::string name;
	std::vector<MD2Triangle> triangles;
};

class MD2File : public ModelFile
{

public:

	bool load(std::wstring pn);

	void loadTex(std::string tfn);

	void draw() { m_Model.draw(); }

	void init() { m_Model.init(); };

	void update() { m_Model.update(); }

private:

	std::string readSkinName();

	int readUVs();
	int readFaces();
	int readFrames();

	void addModelAnimation();

	void addModelObjects();

	AniModel m_Model;

	MD2Header m_Header;

	std::vector<UV> m_uvs;
	std::vector<ModelFace> m_faces;
	std::vector<MD2KeyFrame> m_kfs;
};