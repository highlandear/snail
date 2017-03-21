#include "Impl.hpp"
#include "global.hpp"
#include "gdraw.hpp"
#include "tex.hpp"
#include "gmath.hpp"

void CameraTest::init()
{
	global::gset();

	m_Cam = Camera( 0.0f, 0.0f, 0.0f,
					0.0f, 0.0f, -10.0f,
					0.0f, 1.0f, 0.0f);

	LightManager::onDefault();
	TexManager::loadBmpTexrure(L"box", L"tex\\box.bmp");
	TexManager::attach(L"box");
	
	m_fDeg = 5;
}

void CameraTest::update()
{
//	m_Cam.setViewByMouse();

	if (isKeyDown('W'))
		m_Cam.go(getCamSpeed());
	else if (isKeyDown('S'))
		m_Cam.go(- getCamSpeed());

	if (isKeyDown('A'))
		m_Cam.yaw(getCamSpeed());
	else if (isKeyDown('D'))
		m_Cam.yaw(- getCamSpeed());

	if (isKeyDown(VK_SPACE))
		m_Cam.up(getCamSpeed());
	else if (isKeyDown(VK_CONTROL))
		m_Cam.up(-getCamSpeed());

	if(isKeyDown(VK_UP))
		m_Cam.dup(getCamSpeed());
	else if (isKeyDown(VK_DOWN))
		m_Cam.dup(-getCamSpeed());

	if (isKeyDown(VK_LEFT))
	{
		m_Cam.roll(_DEG2RAD(m_fDeg), 0.0f, 1.0f, 0.0f);
	}
	else if (isKeyDown(VK_RIGHT))
	{
		m_Cam.roll(_DEG2RAD(-m_fDeg), 0.0f, 1.0f, 0.0f);
	}

//	Impl::update();

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

		TexManager::enable();
		gdraw::drawCube();
		TexManager::disable();
	}
	glLoadIdentity();
	glFlush();
}

float CameraTest::getCamSpeed()
{
	return isKeyDown(VK_SHIFT) ? 0.3f : 0.1f;
}


