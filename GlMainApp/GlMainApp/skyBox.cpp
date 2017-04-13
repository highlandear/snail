#include "skyBox.hpp"
#include "tex.hpp"

void SkyBox::init()
{
	// 加载 上、下、左、右、前、后 6 张纹理
	TexManager::loadBmpTexrure(L"top", L"sky\\top.bmp");
	TexManager::loadBmpTexrure(L"bottom", L"sky\\bottom.bmp");
	TexManager::loadBmpTexrure(L"left", L"sky\\left.bmp");
	TexManager::loadBmpTexrure(L"right", L"sky\\right.bmp");
	TexManager::loadBmpTexrure(L"front", L"sky\\front.bmp");
	TexManager::loadBmpTexrure(L"back", L"sky\\back.bmp");
}


void SkyBox::draw()
{
	GLboolean lp;
	glGetBooleanv(GL_LIGHTING, &lp);
	
	// back
	TexManager::attach(L"back");
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x0, y0 + y_hig, z0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x0, y0, z0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x0 + x_len, y0, z0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x0 + x_len, y0 + y_hig, z0);
	}
	glEnd();

	// front
	TexManager::attach(L"front");
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x0 + x_len, y0 + y_hig, z0 + z_wid);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x0 + x_len , y0, z0 + z_wid);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x0, y0, z0 + z_wid);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x0, y0 + y_hig, z0 + z_wid);
	}
	glEnd();

	// left
	TexManager::attach(L"left");
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x0, y0 + y_hig, z0 + z_wid);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x0, y0, z0 + z_wid);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x0, y0, z0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x0, y0 + y_hig, z0);
	}
	glEnd();

	// right
	TexManager::attach(L"right");
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x0 + x_len, y0 + y_hig, z0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x0 + x_len, y0, z0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x0 + x_len, y0, z0 + z_wid);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x0 + x_len, y0 + y_hig, z0 + z_wid);
	}
	glEnd();

	// top
	TexManager::attach(L"top");
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x0 + x_len, y0 + y_hig, z0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x0 + x_len, y0 + y_hig, z0 + z_wid); 
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x0, y0 + y_hig, z0 + z_wid);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x0, y0 + y_hig, z0);
	}
	glEnd();

	if(lp) glEnable(GL_LIGHTING);
}