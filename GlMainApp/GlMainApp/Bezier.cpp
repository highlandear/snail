#include "Impl.hpp"
#include "gmath.hpp"
#include "gout.hpp"
#include "global.hpp"

GLfloat points[4][3] =
{
	{ -4.0f,  -2.0f,  0.0f },
	{ -2.0f,  3.0f,  2.0f },
	{ 2.0f,  -3.0f, -2.0f },
	{ 4.0f,  2.0f,  0.0f }
};

void Bezier::drawPoints(GLfloat p[][3], int sz)
{
	glBegin(GL_POINTS);
	for (int j = 0; j < sz; j++)
		glVertex3fv(&p[j][0]);
	glEnd();
}

void Bezier::drawBezierCurve(GLfloat points[][3], int sz)
{
	glMap1f(GL_MAP1_VERTEX_3, 0.0f, 100.0f, 3, sz, points[0]);
	glBegin(GL_LINE_STRIP);
	{
		for (int i = 0; i < 100; i++)
		{
			glEvalCoord1f(i);
		}		
	}
	glEnd();

	/* // [GLBegin, GLEnd] 与下面的功能相似， 闭区间
	glMapGrid1f(100, 0.0f, 100.0f);
	glEvalMesh1(GL_LINE, 0, 100);
	*/

}

void Bezier::drawColorfullCurve(GLfloat points[][3], int sz)
{
	GLubyte r, g, b;
	
	glMap1f(GL_MAP1_VERTEX_3, 0.0f, 100.0f, 3, sz, points[0]);
	glMapGrid1f(100, 0.0f, 100.0f);

	for (int i = 0; i < 100; i++)
	{
		r = (GLubyte)gmath::irand() & 0xff;
		g = (GLubyte)gmath::irand() & 0xff;
		b = (GLubyte)gmath::irand() & 0xff;
		glColor3ub(r, g, b);
		glEvalMesh1(GL_LINE, i, i + 1);
	}
}

void Bezier::init()
{
	global::gset();

	glEnable(GL_MAP1_VERTEX_3);

	m_nPointNum = 2;

	m_bColorfull = false;
}

void Bezier::update()
{
	if (isKeyDown('2'))
		m_nPointNum = 2;
	else if (isKeyDown('3'))
		m_nPointNum = 3;
	else if (isKeyDown('4'))
		m_nPointNum = 4;
	
	if (isKeyDown('C'))
		m_bColorfull = true;
	else if (isKeyDown('V'))
		m_bColorfull = false;
}

void Bezier::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	  /**< 清除缓存 */
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -13.0f);

	glColor3f(1.0f, 1.0f, 1.0f);

	if (m_bColorfull)
		drawColorfullCurve(points, m_nPointNum);
	else
		drawBezierCurve(points, m_nPointNum);

	glColor3f(1.0f, 0.0f, 0.0f);

	glPointSize(6.0);

	drawPoints(points, m_nPointNum);
	
	glLoadIdentity();
	glColor3f(0.0f, 1.0f, 0.0f);
	gout::wprint(usage(), -2.5f, -1.5f, -5.0f);

	glFlush();
}

std::wstring Bezier::usage()
{
	return L"按键2、3、4， 分别为线性、二次、三次贝赛尔贝曲线";
}