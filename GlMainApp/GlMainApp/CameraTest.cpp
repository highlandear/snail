#include "Impl.hpp"
#include "global.hpp"
#include "gdraw.hpp"
#include "tex.hpp"
#include "gout.hpp"

void CameraTest::init()
{
	global::gset();

	m_Cam = Camera( 0.0f, 0.0f, 10.0f,
					0.0f, 0.0f, -10.0f,
					0.0f, 1.0f, 0.0f);

	LightManager::onDefault();
	TexManager::loadBmpTexrure("box", "tex\\box.bmp");

	

	m_TDSFile = TDSFile();
	m_TDSFile.load(L"model\\main.3ds");
	m_TDSFile.init();

	m_MD2File = MD2File();
	m_MD2File.load(L"model\\monster.md2");
	m_MD2File.loadTex("model\\hobgoblin.bmp");
	m_MD2File.init();
}

void CameraTest::update()
{
	m_Cam.update();

	Impl::update();


	m_MD2File.update();


}

void CameraTest::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	m_Cam.set();
	{
		glTranslatef(0.0f, -3.0f, -0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		gdraw::drawGrid(30.0f, 1.0f);

		glPushMatrix();
		glScalef(3.0f, 3.0f, 3.0f);
		m_TDSFile.draw();
		glPopMatrix();

		TexManager::attach("model\\hobgoblin.bmp");
		glPushMatrix();
		glScalef(0.1f, 0.1f, 0.1f);
		glTranslatef(60.0f, 25.0f, 0.0f);
		m_MD2File.draw();
		glPopMatrix();

		glTranslatef(0.0f, 1.0f, -10.0f);

		TexManager::attach("box");
		glRotatef(getParam(), 1.0f, 1.0f, 0.0f);		
		gdraw::drawCube();
		
		TexManager::disable();
		glLoadIdentity();
		glColor3f(1.0f, 0.0f, 0.0f);
		gout::wprint(usage(), -2.5f, 1.5f, -5.0f);
	}
	glFlush();
}

std::wstring CameraTest::usage()
{
	return L"WSAD : 前后左右平移; 上下左右：上下，顺时针，逆时针; Ctrl键：跟随鼠标";
}

