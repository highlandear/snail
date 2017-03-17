#pragma once
#include <windows.h>
#include <gl/GL.h>

class GLight 
{
public:

	GLight(int i) : id(i) {}

	GLight() : id(0){}

	int getID() { return id; }

	void setID(int i) { id = i; }

	// ���ù�Դλ��
	void GLight::setPosV(const float v[])
	{
		glLightfv(id, GL_POSITION, v);		
	}

	// ���û�����
	void GLight::setAmbientV(const float v[])
	{
		glLightfv(id, GL_AMBIENT, v);		
	}

	// ���������
	void GLight::setDiffuseV(const float v[])
	{
		glLightfv(id, GL_DIFFUSE, v);		
	}

	// ���������
	void GLight::setSpecularV(const float v[])
	{
		glLightfv(id, GL_SPECULAR, v);		
	}

	// ����
	void GLight::setAttenuationV(const float v[])
	{
		glLightfv(id, GL_LINEAR_ATTENUATION, v);
	}

	void GLight::getPosV(float * p)
	{
		glGetLightfv(id, GL_POSITION, p);
	}

	bool available() { return  0 != id; }
	

	void off()
	{
		glDisable(id);
	}

	void on()
	{
		glEnable(id);
	}

	void drop()
	{
		off(); 
		id = 0;
	}

private:
	
	int id;	
};

class LightManager
{
public:
	static GLight & light(int index) { return lights[index]; }
	static void on(int index) { lights[index].setID(ID_START + index); lights[index].on(); }
	static bool isOn(int index) { return lights[index].available(); }
	static void off(int index) { lights[index].off(); }
	static void enable() { glEnable(GL_LIGHTING); }
	static void disable() { glDisable(GL_LIGHTING); }
	static bool isEnabled(){return GL_TRUE == glIsEnabled(GL_LIGHTING);}

	/*
		0�Ź�Դ��ΪĬ�Ϲ�Դ GL_LIGHT0
	*/
	static void onDefault();
	static void offDefault() { off(0); }
	static GLight& getDefault() { return lights[0]; }

	static void offAll()
	{
		for (int i = 0; i < 8; i++)
			off(i);
	}

private:

	static GLight lights[8];

	static const int ID_START = GL_LIGHT0; 
};