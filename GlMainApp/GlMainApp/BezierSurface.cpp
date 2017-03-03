#include "Impl.hpp"
#include "global.hpp"
#include "tex.hpp"
#include "gout.hpp"
/*
	曲面控制点
*/
GLfloat spoints[4][4][3] = {
	{ { -0.8f, -0.6f, 0.8f },{ -0.2f, -0.6f, 1.6f },{ 0.2f, -0.6f, -0.4f },{ 0.6f, -0.6f,  0.8f } },
	{ { -0.6f, -0.2f, 0.8f },{ -0.2f, -0.2f, 1.6f },{ 0.2f, -0.2f, -0.4f },{ 0.6f, -0.2f,  0.8f } },
	{ { -0.6f,  0.2f, 0.8f },{ -0.2f, -0.2f, 0.4f },{ 0.2f,  0.2f,  0.0f },{ 0.3f,  0.2f, -0.4f } },
	{ { -0.6f,  0.6f, 0.8f },{ -0.2f,  0.6f, 0.4f },{ -0.8f,  0.6f,  0.0f },{ 0.8f,  0.6f, -0.4f } }
};

GLfloat texpts[2][2][2] = { { { 0.0, 0.0 },{ 0.0, 1.0 } },{ { 1.0, 0.0 },{ 1.0, 1.0 } } };


void drawPoints()
{
	glBegin(GL_POINTS);
	int u = 4;
	int v = 4;
	for (int i = 0; i < u; i++)
	{
		for (int j = 0; j < v; j++)
		{
			glVertex3fv(spoints[i][j]);
		}
	}
	glEnd();
}

void BezierSurface::init()
{
	global::gset();

	global::setDefaultLight();

	global::setDefaultMaterial();
	glEnable(GL_TEXTURE_2D);
	
	TexManager::loadBmpTexrure(L"sea", L"tex\\sea.bmp");
	TexManager::loadBmpTexrure(L"leaf", L"tex\\leaf.bmp");
	TexManager::attach(L"sea");

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glEnable(GL_AUTO_NORMAL);

	m_eMode = GL_FILL;
	glDisable(GL_LIGHTING);

	m_nU = 4;
	m_nV = 4;

}
void BezierSurface::drawBezierSurface(int uz, int vz)
{
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, uz, 0, 1, 12, vz, &spoints[0][0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, &texpts[0][0][0]);

	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);

	glEvalMesh2(m_eMode, 0, 20, 0, 20);

}

void BezierSurface::update()
{
	if (isKeyDown('O'))
	{
		glEnable(GL_LIGHTING);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glDisable(GL_LIGHTING);
	}
		
	if (isKeyDown('F'))
		m_eMode = GL_FILL;
	else if (isKeyDown('L'))
		m_eMode = GL_LINE;

	if (isKeyDown('1'))
		m_nU = 1;
	else if (isKeyDown('2'))
		m_nU = 2;
	else if (isKeyDown('3'))
		m_nU = 3;
	else if (isKeyDown('4'))
		m_nU = 4;

	if (isKeyDown('Z'))
		m_nV = 1;
	else if (isKeyDown('X'))
		m_nV = 2;
	else if (isKeyDown('C'))
		m_nV = 3;
	else if (isKeyDown('V'))
		m_nV = 4;
	Impl::update();

}

void BezierSurface::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -13.0f);
	glRotatef(getParam(), 1.0, 1.0, 1.0);
	glScalef(3.0f, 3.0f, 3.0f);

	drawBezierSurface(m_nU, m_nV);

	glColor3f(0.0f, 1.0f, 0.0f);
	glPointSize(6.0);
	drawPoints();
	
	// 写帮助
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glColor3f(0.0f, 1.0f, 0.0f);
	gout::wprint(usage(), -2.5f, -1.5f, -5.0f);
	glEnable(GL_LIGHTING);

	glFlush();
}

std::wstring BezierSurface::usage()
{
	return L"1234： U方向的控制点数；ZXCV：V方向的控制点数\n字母O:打开光源, F: GL_FILL, L: GL_LINE\n";
}