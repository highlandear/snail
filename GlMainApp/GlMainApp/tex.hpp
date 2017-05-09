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
	纹理数据 类
*/
class Tex
{
public:
	Tex() : m_uType(GL_RGB), m_pData(0){}

	~Tex() { _SAFE_DEL_ARRAY(m_pData); }
	virtual bool load(std::string pn) = 0;
	virtual bool load(std::wstring wpn) = 0;

	int setTexture();

	void setTextureID(UINT id) { m_uID = id; }

	UINT getTextureID() { return m_uID; }

protected: 

	int m_nWith;						// bmp的宽度
	int m_nHight;						// bmp的高度
	unsigned int m_uType;				// GL_RGB 或GL_RGBA
	unsigned char * m_pData;

private:
	UINT m_uID;
};

/**
	使用像素定义的纹理 类
*/
class RawTex : public Tex
{
public:
//	RawTex( GLfloat c[]): m_pData(c) {}
//	RawTex(std::wstring n):m_pData(simple_data) {}

//	bool load();

	static GLfloat simple_data[];
};

/**
	bitmap纹理 类
*/
class BmpTex : public Tex
{
public:
	bool load(std::string pns);
	bool load(std::wstring wpns);

private:
	static const int BITMAP_FLAG = 0x4D42;
};

class TgaTex : public Tex
{
public:
	bool load(std::string pn); 
	bool load(std::wstring wpn);
};

/**
	纹理管理器
*/
class TexManager
{
public:
	typedef std::unordered_map<std::string, unsigned int> TMAP;

	static void TexManager::put(std::string name, int tid){tmap[name] = tid;}

	static unsigned int get(std::string n);
	
	static bool attach(std::string n);	

	static void detachAll();
	
	static void clear();

	static void loadBmpTexrure(std::string name, std::string fpn);

	static void loadTgaTexrure(std::string name, std::string fpn);
	
//	static void loadRawTexrure(std::wstring name);

	static void enable() { glEnable(GL_TEXTURE_2D); }

	static void disable() { glDisable(GL_TEXTURE_2D); }
	
private:

	static TMAP tmap;			// <texture name : texture id>
};
