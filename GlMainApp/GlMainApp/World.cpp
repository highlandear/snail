#include "Impl.hpp"
#include "global.hpp"
#include "gdraw.hpp"
#include "tex.hpp"
#include "gout.hpp"

void World::init()
{
	global::gset();

	m_Cam = Camera
	(
		
		50.0f, 190.0f, 50.0f,
		-10.0f, 190.0f, -10.0f,
		0.0f, 1.0f, 0.0f
	);
	m_Cor = Coord(0.0f, 190.0f, 0.0f, 1.0f);

	LightManager::onDefault();
	TexManager::loadBmpTexrure(L"box", L"tex\\box.bmp");
//	TexManager::attach(L"box");

	m_Ter = Terrain(L"ter\\terrain.raw", 1024, 1024, 16);
	m_Ter.load();
}

void World::update()
{
	m_Cam.update();

	Impl::update();
}

void World::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(0.0f, 1.0f, 0.0f);
	 m_Cam.set();
	{
		glTranslatef(0.0f, 0.0f, -10.0f);
		
		glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslatef(0, 190, 0);
		gdraw::drawBall(0.5f);
		glPopMatrix();

		m_Ter.drawPoints();
		m_Ter.drawGridPoints();
		glLoadIdentity();
		gout::wprint(usage(), -2.5f, 1.5f, -5.0f);
	}
	glFlush();
}

std::wstring World::usage()
{
	return L"WSAD : 前后左右平移; 上下左右：上下，顺时针，逆时针; Ctrl键：跟随鼠标";
}

