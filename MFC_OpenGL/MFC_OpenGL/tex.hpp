#pragma once
#include <string>
#include <unordered_map>
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#define TEX_MOD GL_TEXTURE_2D

typedef std::unordered_map<std::wstring, unsigned int> TMAP;

class Texes
{
public:	
	static void put(std::wstring n, unsigned int tid)
	{
		tmap[n] = tid;
	}

	static unsigned int get(std::wstring n)
	{
		TMAP::const_iterator it = tmap.find(n);
		if (it == tmap.end())
			return 0;

		return it->second;
	}

	static bool attach(std::wstring n)
	{
		unsigned tid = get(n);
		if (0 == tid) return false;		
		
		glBindTexture(TEX_MOD, tid);
		glEnable(TEX_MOD);

		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glEnable(GL_AUTO_NORMAL);
		glEnable(GL_NORMALIZE);
		glEnable(GL_TEXTURE_GEN_R);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T); 
		
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

		return true;
	}

	static void detachAll()
	{
		glBindTexture(TEX_MOD, 0);
		glDisable(TEX_MOD);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	}

	static void clear()
	{
		detachAll();
		tmap.clear();
		glDisable(TEX_MOD);
	}

private:

	static TMAP tmap;			// <texture name, texture id>
};

class Tex
{
public:
	Tex(std::wstring n) : name(n) {}
	std::wstring getName() { return name; }
	void setName(std::wstring n) { name = n; }
	void addnew(unsigned int tid) { Texes::put(name, tid); }

	virtual void load() = 0;
	
private:
	std::wstring  name;			// name

};

class JpgTex : public Tex
{
public:
	JpgTex(std::wstring n) : Tex(n){}
	void operator()() {  }
	virtual void load();
};

class RawTex : public Tex
{
public:
	RawTex(std::wstring n, GLfloat c[]) : Tex(n) , clr(c){}
	RawTex(std::wstring n) : Tex(n), clr(simple_data) {}
	void operator()() {}
	virtual void load();

	static GLfloat simple_data[];
private:
	GLfloat  * clr;	
};

class TexTest
{
public:
	static void loadAll()
	{
		std::wstring fpn = L"C:\\Users\\hzs\\Desktop\\me\\2.jpg";
		JpgTex(fpn).load();
		fpn = L"C:\\Users\\hzs\\Desktop\\me\\3.jpg";
		JpgTex(fpn).load();
		RawTex(L"show").load();
	}
};

