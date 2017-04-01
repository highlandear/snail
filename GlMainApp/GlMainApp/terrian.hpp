#pragma once
#include "tex.hpp"

class Terrain
{
public:

	Terrain(std::wstring hmpn, int w, int h, int s); 
	Terrain() { m_pData = NULL; }

	~Terrain() { _SAFE_DEL_ARRAY(m_pData); }

	bool load();

	void init();

	void setTexName(std::wstring n) { m_szTexName = n; }

	/*
		 ��ȡ���� (row, col)�ĸ߶�ֵ
	*/
	int find(int row, int col);

	/*
		���� x - zƽ���ϵ����꣬��ȡ���� y �ĸ߶�ֵ
	*/
	int getAveHeight(float x, float z);


	void draw();

	/*
		�߶�ͼ�е�0 - 255 ������߶ȵĶ�Ӧ��ϵ
	*/
	float floatHeight(unsigned char v) { return (float)v; }

	void drawGrid();

	void drawPoints();

	void drawGridPoints();

	void drawSign();

	void setTexCoord(float x, float z);

private:
	std::wstring m_szHeightMapName; // �ر�߶������ļ�
	std::wstring m_szTexName;		// �ر�����

	int m_width;					// ���� X�����ϵĶ�����
	int m_height;					// ���� Z�����ϵĶ�����
	int m_scale;					// ÿһ����

	unsigned char * m_pData;        // ��Ÿ߶���Ϣ

};
