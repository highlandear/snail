#include "Impl.hpp"
#include "global.hpp"
#include "tex.hpp"
#include "gout.hpp"
#include "illuminant.hpp"

Quadrics::~Quadrics()
{
	if (NULL != m_pQuadric)
	{
		gluDeleteQuadric(m_pQuadric);
		m_pQuadric = NULL;
	}
	
	//global::shutDefaultDown();
	LightManager::offDefault();
}

void Quadrics::init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	TexManager::clear();
	TexManager::loadBmpTexrure("galaxy", "tex\\galaxy.bmp");
	TexManager::loadBmpTexrure("sea", "tex\\sea.bmp");
	TexManager::loadBmpTexrure("web", "tex\\web.bmp");
	TexManager::loadBmpTexrure("leaf", "tex\\leaf.bmp");
//	TexManager::loadRawTexrure(L"raw");

	LightManager::onDefault();

	m_pQuadric = gluNewQuadric();
	gluQuadricNormals(m_pQuadric, GLU_SMOOTH);
	gluQuadricTexture(m_pQuadric, GL_TRUE);

	gluQuadricDrawStyle(m_pQuadric, GLU_FILL);
}

void Quadrics::update()
{
	if (isKeyDown('O'))	
		glDisable(GL_LIGHTING);
	else
		glEnable(GL_LIGHTING);

	//{ GLU_FILL, GLU_LINE, GLU_SILHOUETTE };
	if (isKeyDown('F'))
		gluQuadricDrawStyle(m_pQuadric, GLU_FILL);
	else if (isKeyDown('L'))
		gluQuadricDrawStyle(m_pQuadric, GLU_LINE);
	else if (isKeyDown('S'))
		gluQuadricDrawStyle(m_pQuadric, GLU_SILHOUETTE);

	Impl::update();
}

void Quadrics::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -8.0f);
	
	// 绘制圆柱体	
	TexManager::attach("web");
	glPushMatrix();
	{
		glTranslatef(-2.0f, 1.1f, 0.0f);
		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glRotatef(getParam(), 1.0f, 0.0f, 1.0f);
		gluCylinder(m_pQuadric, 0.8f, 0.8f, 1.8f, 32, 32);
	}
	glPopMatrix();
	
	// 绘制圆锥体
	//TexManager::attach(L"raw");
	TexManager::attach("sea");
	glPushMatrix();
	{
		glTranslatef(2.0f, 1.1f, 0.0f);
		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glRotatef(getParam(), 1.0f, 0.0f, 1.0f);
		gluCylinder(m_pQuadric, 1.0f, 0.0f, 1.8f, 32, 32);
	}
	glPopMatrix();
	
	// 绘制圆盘	 
	TexManager::attach("leaf");
	glPushMatrix();
	{
		glTranslatef(-2.0f, -1.1f, 0.0f);
		glRotatef(getParam(), 0.0f, 1.0f, 0.0f);
		gluDisk(m_pQuadric, 0.4f, 1.2f, 32, 32);
	}
	glPopMatrix();
	
	// 绘制球体  
	 TexManager::attach("galaxy");
	glPushMatrix();
	{
		glTranslatef(2.0f, -1.1f, 0.0f);
		glRotatef(getParam(), 0.0f, 1.0f, 0.0f);
		gluSphere(m_pQuadric, 1.1f, 32, 32);
	}
	glPopMatrix();
	
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);	
	gout::wprint(usage(), -6.0f, -5.0f, -5.0f);
	glEnable(GL_LIGHTING);

	glFlush();
}
std::wstring Quadrics::usage()
{
	return L"字母O:关闭光源";
}