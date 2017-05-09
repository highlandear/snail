#include "skyBox.hpp"
#include "tex.hpp"

void SkyBox::init()
{
	// 加载 上、下、左、右、前、后 6 张纹理
	TexManager::loadBmpTexrure("top", "sky\\top.bmp");
	TexManager::loadBmpTexrure("bottom", "sky\\bottom.bmp");
	TexManager::loadBmpTexrure("left", "sky\\left.bmp");
	TexManager::loadBmpTexrure("right", "sky\\right.bmp");
	TexManager::loadBmpTexrure("front", "sky\\front.bmp");
	TexManager::loadBmpTexrure("back", "sky\\back.bmp");
}


void SkyBox::draw()
{
	GLboolean lp;
	glGetBooleanv(GL_LIGHTING, &lp);
	
	// back
	TexManager::attach("back");
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x0, y0 + y_hig, z0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x0, y0, z0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x0 + x_len, y0, z0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x0 + x_len, y0 + y_hig, z0);
	}
	glEnd();

	// front
	TexManager::attach("front");
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x0 + x_len, y0 + y_hig, z0 + z_wid);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x0 + x_len , y0, z0 + z_wid);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x0, y0, z0 + z_wid);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x0, y0 + y_hig, z0 + z_wid);
	}
	glEnd();

	// left
	TexManager::attach("left");
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x0, y0 + y_hig, z0 + z_wid);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x0, y0, z0 + z_wid);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x0, y0, z0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x0, y0 + y_hig, z0);
	}
	glEnd();

	// right
	TexManager::attach("right");
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x0 + x_len, y0 + y_hig, z0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x0 + x_len, y0, z0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x0 + x_len, y0, z0 + z_wid);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x0 + x_len, y0 + y_hig, z0 + z_wid);
	}
	glEnd();

	// top
	TexManager::attach("top");
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