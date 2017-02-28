#pragma once
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include "keyStatus.hpp"

#ifndef _IMPL_CLASS
#define _IMPL_CLASS Fog
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
	һЩʾ���ľ���ʵ��
**/

class Impl
{
public:
	Impl() : m_Angle(0.0f) {}

	virtual void draw() = 0;
	
	virtual void init() = 0;
	
	virtual float getSpeed() { return 5.0f;}		// Ĭ�ϵ��ٶ�

	bool isKeyDown(UINT keyID) { return KeyStatus::isKeyDown(keyID); }

	virtual void update() { reto(m_Angle, getSpeed()); }

	float getParam() { return m_Angle;	}

	void reto(float & v, float a) { v = (v + a) > 360 ? 0 : (v + a); }

private:

	float m_Angle;								// ������ת
};
/**
	�򵥵Ļ�ͼʾ��
*/
class Cube : public Impl
{
public:
	void draw();
	void init() {}
};

/**
	����
*/
class Material : public Impl
{
public: 
	
	void draw();
	void init();
};

/**
	����
*/
class Light : public Impl
{

public:
	void draw();
	void init();
	void update();

private:

	float m_bRedX;			// ��ɫ�����ת�Ƕ�
	float m_bRedY;
	float m_bGreenX;		// ��ɫ�����ת�Ƕ�
	float m_bGreenY;
	float m_bBlueX;			// ��ɫ�����ת�Ƕ�
	float m_bBlueY;
};

/**
	��ʾ�б�
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
	����
*/
class Texture : public Impl
{	
public:
	~Texture();

	void draw();
	void init();
};

/**
	������
*/
class Antialiasing : public Impl
{
public:
	void draw();
	void init();

	float getSpeed() { return 0.7f; }
};

/**
	��Ч��
*/
class Fog : public Impl
{
	//{ GL_LINEAR, GL_EXP, GL_EXP2 };		// ��Ч��ģʽ
public:
	~Fog();
	void draw();
	void init();

	void update();
private:

	GLfloat m_fZ;
	
	static const int OBJ_NUM = 5;

	static GLfloat s_fnColor[4];			// �����ɫ
};