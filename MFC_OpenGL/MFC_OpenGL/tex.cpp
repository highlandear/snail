#include "stdafx.h"
#include "base.hpp"
#include "tex.hpp"

#include <unordered_map>

TMAP Texes::tmap;

void JpgTex::load()
{
	unsigned tid;
	unsigned char *pData = NULL;
	CImage ci;
	ci.Load(getName().c_str());

	int w = ci.GetWidth();
	int h = ci.GetHeight();

	if (ci.GetPitch() < 0)
	{
		pData = (unsigned char *)ci.GetBits() + (ci.GetPitch()*(h - 1));
	}
	else
	{
		pData = (unsigned char *)ci.GetBits();
	}

	glGenTextures(1, &tid);
	glBindTexture(TEX_MOD, tid);
//	glTexParameteri(TEX_MOD, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(TEX_MOD, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glTexParameteri(TEX_MOD, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(TEX_MOD, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(TEX_MOD, GL_TEXTURE_WRAP_S, GL_REPEAT);//S方向重复  
	glTexParameteri(TEX_MOD, GL_TEXTURE_WRAP_T, GL_REPEAT);//T方向重复 
	glTexImage2D(TEX_MOD, 0, GL_RGB, w, h, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pData);

	//Helper::debug(pData, 10);
	
	addnew(tid);
}
GLfloat RawTex::simple_data[] =
{
	//	红  洋
	//	绿  蓝
	1.0f, 0.0f, 1.0f,1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f
};

void RawTex::load()
{
	unsigned int tid;
	glGenTextures(1, &tid);
	glBindTexture(TEX_MOD, tid);

	glTexParameteri(TEX_MOD, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(TEX_MOD, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(TEX_MOD, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(TEX_MOD, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(TEX_MOD, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, clr);
	addnew(tid);
}
