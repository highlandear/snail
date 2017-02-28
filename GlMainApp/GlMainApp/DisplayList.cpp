#include "Impl.hpp"

void DisplayList::init()
{
	m_uIndex = glGenLists(1);
	if (0 == m_uIndex)
		return;

	glNewList(m_uIndex, GL_COMPILE);	// List start

	glBegin(GL_TRIANGLES);
//	前
	glColor3f(1.0f, 0.0f, 0.0f);		// 
	glVertex3f(0.0f, 1.0f, 0.0f);		// R (0, 1, 0)
	glColor3f(0.0f, 1.0f, 0.0f);		// 
	glVertex3f(-1.0f, -1.0f, 1.0f);		// G (-1, -1, 1)
	glColor3f(0.0f, 0.0f, 1.0f);		// 
	glVertex3f(1.0f, -1.0f, 1.0f);		// B (1, -1, 1)
//	右									
	glColor3f(1.0f, 0.0f, 0.0f);		// 
	glVertex3f(0.0f, 1.0f, 0.0f);		// R (0, 1, 0)
	glColor3f(0.0f, 0.0f, 1.0f);		// 
	glVertex3f(1.0f, -1.0f, 1.0f);		// B (1, -1, 1)
	glColor3f(0.0f, 1.0f, 0.0f);		//
	glVertex3f(1.0f, -1.0f, -1.0f);		// G (1 -1, -1)
// 后									
	glColor3f(1.0f, 0.0f, 0.0f);		//
	glVertex3f(0.0f, 1.0f, 0.0f);		// R (0, 1, 0)
	glColor3f(0.0f, 1.0f, 0.0f);		//
	glVertex3f(1.0f, -1.0f, -1.0f);		// G (1, -1, -1)
	glColor3f(0.0f, 0.0f, 1.0f);		//
	glVertex3f(-1.0f, -1.0f, -1.0f);	// B (-1, -1, -1)
// 左											
	glColor3f(1.0f, 0.0f, 0.0f);		//
	glVertex3f(0.0f, 1.0f, 0.0f);		// R (0, 1, 0)
	glColor3f(0.0f, 0.0f, 1.0f);		//
	glVertex3f(-1.0f, -1.0f, -1.0f);	// B (-1, -1, -1)
	glColor3f(0.0f, 1.0f, 0.0f);		//
	glVertex3f(-1.0f, -1.0f, 1.0f);		// G (-1, -1, 1)
	glEnd();

// 画底
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);		//
	glVertex3f(-1.0f, -1.0f, 1.0f);		// R (-1, -1, 1)
	glColor3f(0.0f, 1.0f, 0.0f);		//
	glVertex3f(1.0f, -1.0f, 1.0f);		// G (1, -1, 1)
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);		// B (1, -1, -1)
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);	// P (-1, -1, -1)
	glEnd();
	
	glEndList();							// List end

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}

void DisplayList::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		/**< 清除颜色和深度缓存 */
	glLoadIdentity();

	// 绘制12个金字塔体
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			glLoadIdentity();
			glTranslatef(-3.0 + 2.0 * x, -2.0 + 2.0 * y, -10.0f);
			glScalef(0.8f, 0.8f, 0.8f);
			glRotatef(getParam(), 1.0f, 1.0f, 0.0f);
			glCallList(m_uIndex); 
		}
	}
	glFlush();
}