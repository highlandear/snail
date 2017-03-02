#pragma once
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#ifndef CALLBACK
#define CALLBACK    __stdcall
#endif // !CALLBACK

class tess
{
public:
	static void CALLBACK tessBeginCB(GLenum which);
	static void CALLBACK tessEndCB();
	static void CALLBACK tessErrorCB(GLenum errorCode);
	static void CALLBACK tessVertexCB(const GLvoid *data);
	static void CALLBACK tessCombineCB(GLdouble coords[3], GLdouble *vertex_data[4], GLfloat weight[4], GLdouble **dataOut);
	static GLuint tesselateCQuad(GLdouble v, GLdouble b = GL_FALSE);

private:
	static const int MAX_INTER_NUM = 32;
	
	static GLdouble vertex[MAX_INTER_NUM][6]; // 存储交点[交点个数] [交点坐标，交点RGB]
};
