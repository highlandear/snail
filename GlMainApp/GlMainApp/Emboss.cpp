#include "Impl.hpp"
#include "global.hpp"
#include "tex.hpp"
#include "gout.hpp"
#include "gdraw.hpp"

#include "illuminant.hpp"
#include "gmath.hpp"

PFNGLACTIVETEXTUREARBPROC      Emboss::glActiveTextureARB = NULL;
PFNGLMULTITEXCOORD2FARBPROC    Emboss::glMultiTexCoord2fARB = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC Emboss::glClientActiveTextureARB = NULL;

Emboss::VertexInfo Emboss::g_VerInfo[] =
{
	//   tu    tv     nx    ny     nz     x      y     z 
	{ 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,  -1.0f, -1.0f, 0.0f },
	{ 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, -1.0f, 0.0f },
	{ 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  -1.0f,  1.0f, 0.0f },
	{ 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,   1.0f,  1.0f, 0.0f }
};

void Emboss::init()
{
	if (! gout::isExtSupported("GL_ARB_multitexture"))
		return;

	glActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");
	glClientActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glClientActiveTextureARB");

	if (! glActiveTextureARB || !glMultiTexCoord2fARB || !glClientActiveTextureARB)
		return;

	global::gset();

	TexManager::loadTgaTexrure(L"woodfloor", L"tex\\woodfloor.tga");
	
//	if (! TexManager::attach(L"woodfloor"))
//		return;

	m_uTexID = TexManager::get(L"woodfloor");

	m_fRedis = 2.0f;

	LightManager::onDefault();
	m_Light = LightManager::getDefault();
	GLfloat lp [] = { m_fRedis, 0.0f, -5.0f, 1.0f };	// 光源位置
	m_Light.setPosV(lp);
}

void Emboss::update()
{
	if (isKeyDown('L'))
		LightManager::disable();
	else
		LightManager::enable();

	Impl::update();
}


void drawQuad()
{
	glBegin(GL_QUADS);
	glEnd();
}
void Emboss::start()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ZERO);

	// 两个相同纹理叠加 第 0 个
	glActiveTextureARB(GL_TEXTURE0_ARB);
	TexManager::attach(L"woodfloor");

	// 纹理环境模式为组合函数方式。
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);

	// 指定RGB操作方式是乘法
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_MODULATE);

	// 对颜色分量的缩放操作 加亮图像颜色
	glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_EXT, 2.0f);

	// alpha的操作方式  替换方式
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT, GL_REPLACE);


	// 两个相同纹理叠加 第 1 个
	glActiveTextureARB(GL_TEXTURE1_ARB);
	TexManager::attach(L"woodfloor");

	// 纹理环境模式为组合函数方式
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);

	// RGB操作方式为替换
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_REPLACE);

	// RGB缩放操作
	glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_EXT, 1.0f);

	// 将前面纹理的结果作为输入
	glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_RGB_EXT, GL_PREVIOUS_EXT);


	// alpha操作的方法
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT, GL_ADD_SIGNED_EXT);
	glTexEnvf(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA_EXT, GL_ONE_MINUS_SRC_ALPHA);

	// 指定操作数一个是是纹理alpha ，另一个是先前的alpha
	glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_EXT, GL_TEXTURE);
	glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE1_ALPHA_EXT, GL_PREVIOUS_EXT);

	glBegin(GL_TRIANGLE_STRIP);
	{
		for (int i = 0; i < 4; ++i)
		{
			glNormal3f(g_VerInfo[i].nx, g_VerInfo[i].ny, g_VerInfo[i].nz);

			///指定纹理单元0的纹理坐标
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, g_VerInfo[i].tu, g_VerInfo[i].tv);

			///指定纹理单元1的纹理坐标
			//glMultiTexCoord2fARB(GL_TEXTURE1_ARB, g_fEmbossTexCoords[i].tu2, g_fEmbossTexCoords[i].tv2);

			///指定顶点坐标
			glVertex3f(g_VerInfo[i].x, g_VerInfo[i].y, g_VerInfo[i].z);
		}
	}
	glEnd();


	///恢复状态,关闭两个纹理单元
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glDisable(GL_TEXTURE_2D);
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glDisable(GL_TEXTURE_2D);

	///关闭混合
	glDisable(GL_BLEND);
}
void Emboss::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);

	TexManager::disable();
	GLboolean e = LightManager::isEnabled();	
	LightManager::disable();

	float p[] = { m_fRedis * gmath::dsin(getParam()), m_fRedis * gmath::dcos(getParam()), -5.0f, 1.0f };
	m_Light.setPosV(p);
	glTranslatef(p[0], p[1], p[2]);
	gdraw::drawBall(0.1);

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -7.0f);
//	glRotatef(getParam(), 1.0f, 1.0f, 0.0f);	
	if(e)
		LightManager::enable();
	TexManager::enable();
	gdraw::drawCube();
	//start();

	// TODO:

	glFlush();
}