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
	TexManager::loadBmpTexrure(L"box", L"tex\\box.bmp");
	TexManager::attach(L"box");	
}

void CameraTest::update()
{
	m_Cam.update();

	Impl::update();
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
		
		glTranslatef(0.0f, 1.0f, -10.0f);

		TexManager::enable();
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
	return L"WSAD : ǰ������ƽ��; �������ң����£�˳ʱ�룬��ʱ��; Ctrl�����������";
}

