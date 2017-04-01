#include "Impl.hpp"
#include "global.hpp"
#include "tex.hpp"
#include "gout.hpp"
#include "gdraw.hpp"

void World::init()
{
	global::gset();

	m_Cam = Camera
	(
		
		300.0f, 210.0f, 300.0f,
		500.0f, 190.0f, 500.0f,
		0.0f, 1.0f, 0.0f
	);

//	LightManager::onDefault();
	TexManager::loadBmpTexrure(L"terrain", L"tex\\terrain.bmp");
	TexManager::loadBmpTexrure(L"box", L"tex\\box.bmp");

	m_Ter = Terrain(L"ter\\terrain.raw", 1024, 1024, 16);
	m_Ter.load();

	LightManager::disable();
}

void World::update()
{
	m_Cam.update();

	if(isKeyDown('L'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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

		m_Ter.drawSign();
	//	m_Ter.drawPoints();
		m_Ter.drawGridPoints();	
		TexManager::attach(L"terrain");

		m_Ter.drawGrid();

		TexManager::attach(L"box");

		float x0 = 300.0f;
		float z0 = 300.0f;
		float y0 = m_Ter.getAveHeight(x0, z0);
		gdraw::drawCube(x0, y0, z0, 10.0f);
		glLoadIdentity();
		gout::wprint(usage(), -2.5f, 1.5f, -5.0f);
	}
	glFlush();
}

std::wstring World::usage()
{
	return L"WSAD : 前后左右平移; 上下左右：上下，顺时针，逆时针; Ctrl键：跟随鼠标";
}

