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
		
		300.0f, 310.0f, 300.0f,
		500.0f, 290.0f, 500.0f,
		0.0f, 1.0f, 0.0f
	);

	m_Ter = Terrain(L"ter\\terrain.raw", 1024, 1024, 16);
	m_Ter.load();
	m_Ter.init();

	m_Sky = SkyBox(0, 170, 0, 1024, 1024, 600 );
	m_Sky.init();

//	m_Model = TDSModel();
	m_TDSFile = TDSFile();
	m_TDSFile.load(L"3ds\\main.3ds");

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
	//	m_Ter.drawGridPoints();	

		m_Ter.draw();
		
		m_Sky.draw();

		m_Ter.drawBox(300.0f, 300.0f);
		
		glLoadIdentity();
		glColor3f(1.0f, 1.0f, 1.0f);
		gout::wprint(usage(), -2.5f, 1.5f, -5.0f);
	}
	glFlush();
}

std::wstring World::usage()
{
	return L"WSAD : 前后左右平移; 上下左右：上下，顺时针，逆时针; Ctrl键：跟随鼠标";
}

