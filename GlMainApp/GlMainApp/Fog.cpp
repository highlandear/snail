#include "Impl.hpp"
#include "gout.hpp"
#include "base.hpp"


#include"global.hpp"

#include "illuminant.hpp"

Fog::~Fog()
{
	LightManager::onDefault();
	glDisable(GL_FOG);
}

GLfloat Fog::s_fnColor[4] = { 0.5,0.5,0.5,1.0 };

void Fog::init()
{
	LightManager::onDefault();
	// ��Ч
	glEnable(GL_FOG);
	{
		glFogi(GL_FOG_MODE, GL_LINEAR);				// ������Ч��ģʽ
		glFogfv(GL_FOG_COLOR, s_fnColor);			// ָ�������ɫ
		glFogf(GL_FOG_DENSITY, 0.5f);				// �������Ũ��
		glFogf(GL_FOG_START, 1.0);					// ����������Ŀ�ʼλ��
		glFogf(GL_FOG_END, 10.0);					// ����������Ľ���λ��
		glHint(GL_FOG_HINT, GL_NICEST);				// �涨��Ч������
	}

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	m_fZ = -5.0f;
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

void Fog::update()
{
	if (isKeyDown('F'))
	{
		glDisable(GL_FOG);
	}
	else
	{
		glEnable(GL_FOG);
	}

	if (isKeyDown('W')) 
		m_fZ += 0.2f; 

	else if (isKeyDown('S'))			// ͬʱ����W ��Ч
		m_fZ -= 0.2f;

	if (isKeyDown('1'))
	{
		glFogi(GL_FOG_MODE, GL_LINEAR);	 // ������Ч��ģʽ
	}
	else if (isKeyDown('2'))
	{
		glFogi(GL_FOG_MODE, GL_EXP);	 // ������Ч��ģʽ
	}
	else if (isKeyDown('3'))			// ���ȼ��� 1 > 2 > 3
	{
		glFogi(GL_FOG_MODE, GL_EXP2);		
	}
}

void Fog::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	float r = 0.5f;

	glEnable(GL_LIGHTING);
	{
		for (int i = 0; i < OBJ_NUM; i++)

			gdraw::drawTeaPot(r, i - 1.0f, 0.0f, (m_fZ - i));
	}	
	glDisable(GL_LIGHTING);

	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	gout::wprint(usage(), -1.5f, 1.0f, -5.0f);

	glFlush();
}

std::wstring Fog::usage()
{
	return L"��-Ч����ʹ�÷���:\nF: �ر���Ч��\nW:��ǰ��D:���\n1��2��3�ֱ���������ģʽ";
}