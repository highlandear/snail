#include "Impl.hpp"
#include "gout.hpp"
#include "tess.hpp"

Tessellation::~Tessellation()
{
	glDeleteLists(m_uList, LIST_NUM);
}

void Tessellation::init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	GLdouble v = GLU_TESS_WINDING_ODD;
	m_uList = tess::tesselateCQuad(v);
}

void Tessellation::update()
{
	if (isKeyDown('F'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	else if(isKeyDown('L'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	int v = 0;
	int b = GL_FALSE;

	if (isKeyDown('1'))
		v = GLU_TESS_WINDING_ODD;
	else if (isKeyDown('2'))
		v = GLU_TESS_WINDING_NONZERO;
	else if (isKeyDown('3'))
		v = GLU_TESS_WINDING_POSITIVE;
	else if (isKeyDown('4'))
		v = GLU_TESS_WINDING_NEGATIVE;
	else if (isKeyDown('5'))
		v = GLU_TESS_WINDING_ABS_GEQ_TWO;

	if (0 != v)
	{
		glDeleteLists(m_uList, LIST_NUM);
		m_uList = tess::tesselateCQuad(v, b);
	}

	
	if (isKeyDown('B'))
	{
		b = GL_TRUE;
		glDeleteLists(m_uList, LIST_NUM);
		m_uList = tess::tesselateCQuad(v, b);
	}		
	else if (isKeyDown('N'))
	{
		b = GL_FALSE;
		glDeleteLists(m_uList, LIST_NUM);
		m_uList = tess::tesselateCQuad(v, b);
	}		

	Impl::update();			// 继续旋转
}

void Tessellation::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();
	
	glTranslatef(-6.0f, 0.0f, -30.0f);
	glRotatef(getParam(), 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, .0f, 0.0f);
	glScalef(1.5f, 1.5f, 1.5f);
	glCallList(m_uList);
	
	glTranslatef(5.0f, 0.0f, 0.0f);
	glCallList(m_uList + 1);

	glTranslatef(5.0f, 0.0f, 0.0f);
	glCallList(m_uList + 2);

	glPopMatrix();
	
	glColor3f(1.0f, 0.0f, 0.0f);
	gout::wprint(usage(), -2.5f, 1.5f, -5.0f);

	glFlush();
}

std::wstring Tessellation::usage()
{
	return L"F：GL_FILL,L:GL_LINE模式\nB:GL_TESS_BOUNDARY_ONLY is GL_TRUE, N: GL_FALSE\n\
1: GL_TESS_WINDING_ODD, 2:NONZERO, 3: POSITIVE, 4:NEGATIVE, 5:ABS_GEQ_TWO";
}