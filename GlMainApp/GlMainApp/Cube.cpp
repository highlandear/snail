#include "base.hpp"


static GLfloat vertices[] =
{ 
	1.0f,1.0f,-1.0f, 
	-1.0f,1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f 
};

static GLfloat colors[] =
{ 
	1.f,0.f,0.f,
	0.f,1.f,0.f,
	0.f,0.f,1.f,
	1.f,1.f,0.f,
	1.f,0.f,1.f,
	0.f,1.f,1.f,
	0.4f,0.6f,0.3f,
	0.f,0.8f,0.4f
};

static GLbyte indexs[] =
{
	0,1,2,3, // 顶面索引
	4,5,6,7, // 底面索引
	0,3,4,7, // 右面索引
	2,5,4,3, // 前面索引
	2,1,6,5, // 左面索引
	0,1,6,7  // 后面索引
};

void Cube::draw()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -6.0f);

	glRotatef(getParam(), 0.0f, 1.0f, 0.0f);
	glRotatef(getParam() * 0.7f, -1.0f, 0.0f, 0.0f);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_BYTE, &indexs[0]);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_BYTE, &indexs[4]);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, &indexs[8]);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, &indexs[12]);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, &indexs[16]);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_BYTE, &indexs[20]);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glFlush();
}
