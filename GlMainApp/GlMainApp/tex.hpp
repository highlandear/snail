#pragma once
#include <string>
#include <windows.h>
#include <unordered_map>
#include <gl/gl.h>
#include <gl/glu.h>

#ifndef _SAFE_DEL
#define _SAFE_DEL(p) { if(p){delete(p);  (p)=NULL;} }
#endif

#ifndef _SAFE_DEL_ARRAY
#define _SAFE_DEL_ARRAY(p) { if(p){delete[] (p);  (p)=NULL;} }
#endif

/**
	�������� ��
*/
class Tex
{
public:

	Tex(std::wstring n) : m_szName(n) {}

	virtual bool load() = 0;

	void setTextureID(UINT id) { m_uID = id; }

	std::wstring getName() { return m_szName; }

	UINT getTextureID() { return m_uID; }

private:
	std::wstring m_szName;
	UINT m_uID;
};

/**
	ʹ�����ض�������� ��
*/
class RawTex : public Tex
{
public:
	RawTex(std::wstring n, GLfloat c[]) : Tex(n), m_pData(c) {}
	RawTex(std::wstring n) : Tex(n), m_pData(simple_data) {}

	bool load();

	static GLfloat simple_data[];

private:
	GLfloat  * m_pData;
};

/**
	bitmap���� ��
*/
class BmpTex : public Tex
{
public:

	BmpTex(std::wstring n, std::wstring pn) : Tex(n), m_szPathName(pn) {}

	BmpTex(std::wstring pn) : Tex(pn), m_szPathName(pn) {}

	~BmpTex() { _SAFE_DEL_ARRAY(m_pData); }

	bool load();

private:
	std::wstring m_szPathName;			// bmp��ʽͼƬ�ļ�������·����

	int m_nWith;						// bmp�Ŀ��
	int m_nHight;						// bmp�ĸ߶�
	unsigned char * m_pData;			// ��RGB��ʽ��ȡ����������������

	static const int BITMAP_FLAG = 0x4D42;
};

/**
	���������
*/
class TexManager
{
public:
	typedef std::unordered_map<std::wstring, unsigned int> TMAP;
//	static void put(std::wstring n, unsigned int tid);

	static void put(Tex & t);
	
	static unsigned int get(std::wstring n);
	
	static bool attach(std::wstring n);	

	static void detachAll();
	
	static void clear();

//	static void loadTest();
	static void loadBmpTexrure(std::wstring name, std::wstring fpn);
	static void loadRawTexrure(std::wstring name);
	
private:

	static TMAP tmap;			// <texture name : texture id>
};
