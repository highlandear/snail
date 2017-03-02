#pragma once
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include "keyStatus.hpp"
#include <string>

#ifndef _IMPL_CLASS
#define _IMPL_CLASS Quadrics
//#define _IMPL_CLASS Tessellation
//#define _IMPL_CLASS Light
//#define _IMPL_CLASS Fog
//#define _IMPL_CLASS Texture
//#define _IMPL_CLASS Antialiasing
#endif

#ifndef _SAFE_DEL
#define _SAFE_DEL(p) { if(p){delete(p);  (p)=NULL;} }
#endif

#ifndef _SAFE_DEL_ARRAY
#define _SAFE_DEL_ARRAY(p) { if(p){delete[] (p);  (p)=NULL;} }
#endif

/**
	一些示例的具体实现
**/

class Impl
{
public:
	Impl() : m_Angle(0.0f) {}

	virtual void draw() = 0;
	
	virtual void init() = 0;

	std::wstring usage() {}
	
	virtual float getSpeed() { return 5.0f;}		// 默认的速度

	bool isKeyDown(UINT keyID) { return KeyStatus::isKeyDown(keyID); }

	virtual void update() { reto(m_Angle, getSpeed()); }

	float getParam() { return m_Angle;	}

	void reto(float & v, float a) { v = (v + a) > 360 ? 0 : (v + a); }

private:

	float m_Angle;								// 控制旋转
};
/**
	简单的绘图示例
*/
class Cube : public Impl
{
public:
	void draw();
	void init() {}
};

/**
	材质
*/
class Material : public Impl
{
public: 
	
	void draw();
	void init();
};

/**
	光线
*/
class Light : public Impl
{

public:
	void draw();
	void init();
	void update();
	std::wstring usage();

private:

	float m_bRedX;			// 红色球的旋转角度
	float m_bRedY;
	float m_bGreenX;		// 绿色球的旋转角度
	float m_bGreenY;
	float m_bBlueX;			// 蓝色球的旋转角度
	float m_bBlueY;
};

/**
	显示列表
*/
class DisplayList : public Impl
{
public:
	void draw();
	void init();

private:

	UINT m_uIndex;
};

/**
	纹理
*/
class Texture : public Impl
{	
public:
	~Texture();

	void draw();
	void init();
};

/**
	反走样
*/
class Antialiasing : public Impl
{
public:
	void draw();
	void init();

	float getSpeed() { return 0.7f; }
};

/**
	雾化效果
*/
class Fog : public Impl
{
	//{ GL_LINEAR, GL_EXP, GL_EXP2 };		// 雾效的模式
public:
	~Fog();
	void draw();
	void init();

	void update();

	std::wstring usage();
private:

	GLfloat m_fZ;
	
	static const int OBJ_NUM = 5;

	static GLfloat s_fnColor[4];			// 雾的颜色
};

/**
	网格化示例
*/
class Tessellation : public Impl
{
public:
	~Tessellation();
	void init();
	void update();
	void draw();
	std::wstring usage();
	float getSpeed() { return 4.0f; }

private:

	GLuint m_uList;

	const static int LIST_NUM = 3;
};

/**
	二次几何体
*/
class Quadrics :public Impl
{
public:
	~Quadrics();
	void init();
	void update();
	void draw();
	std::wstring usage();

private:
	GLUquadricObj  * m_pQuadric;
};