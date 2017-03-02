#include "tess.hpp"
#include "gmath.hpp"

/* concave quad 凹四边形

        0          2
         \\      //
          \ \  / /
           \  3 /
            \  /
             \/
             1
*/
static GLdouble cquad[4][3] =
{
	{ -3,3,0 },
	{ 0,0,0 },
	{ 3,3,0 },
	{ 0, 2, 0 }
};

/* Hollow quad

     0--------3
     | 4----7 |
     | |    | |
     | 5----6 |
     1--------2
*/
static GLdouble  hquad[8][3] =
{
	{ -2,3,0 },
	{ -2,0,0 },
	{ 2,0,0 },
	{ 2,3,0 },

	{ -1,2,0 },
	{ -1,1,0 },
	{ 1,1,0 },
	{ 1,2,0 }
};

/*
有交叉的五角星
*/
static GLdouble fstar[5][6] =
{
	{ 0.0, 3.0, 0, },       // 0: x,y,z,r,g,b
	{ -1.0, 0.0, 0, },      // 1:
	{ 1.6, 1.9, 0, },       // 2:
	{ -1.6, 1.9, 0, },      // 3:
	{ 1.0, 0.0, 0, }        // 4:
};

void tess::tessBeginCB(GLenum which)
{
	glBegin(which);
}

void tess::tessEndCB()
{
	glEnd();
}

void tess::tessErrorCB(GLenum errorCode)
{
	const GLubyte *errorStr;

	errorStr = gluErrorString(errorCode);
}

void tess::tessVertexCB(const GLvoid *data)
{
	GLdouble* pt;
	GLubyte red, green, blue;
	pt = (GLdouble*)data;
	/** 随即产生颜色值 */
	red = (GLubyte)gmath::irand() & 0xff;
	green = (GLubyte)gmath::irand() & 0xff;
	blue = (GLubyte)gmath::irand() & 0xff;
	glColor3ub(red, green, blue);
	glVertex3dv(pt);
}

GLdouble tess::vertex[MAX_INTER_NUM][6];

void tess::tessCombineCB(GLdouble coords[3], GLdouble *vertex_data[4], GLfloat weight[4], GLdouble **dataOut)
{
	static int i = 0;
	vertex[i][0] = coords[0];
	vertex[i][1] = coords[1];
	vertex[i][2] = coords[2];

	for (int j = 3; j < 6; j++)
	{
		vertex[i][j] = weight[0] * vertex_data[0][i] +
			weight[1] * vertex_data[1][i] +
			weight[2] * vertex_data[2][i] +
			weight[3] * vertex_data[3][i];
	}

	*dataOut = vertex[i++];

	if (i > (MAX_INTER_NUM - 1)) i = 0;
}

GLuint tess::tesselateCQuad(GLdouble v, GLdouble b)
{
	GLuint list = glGenLists(3);
	if (0 == list)
		return 0;

	GLUtesselator * ptor = gluNewTess();
	if (NULL == ptor)
		return 0;

	gluTessCallback(ptor, GLU_TESS_BEGIN, (void (CALLBACK *)())tessBeginCB);
	gluTessCallback(ptor, GLU_TESS_END, (void (CALLBACK *)())tessEndCB);
	gluTessCallback(ptor, GLU_TESS_ERROR, (void (CALLBACK *)())tessErrorCB);
	gluTessCallback(ptor, GLU_TESS_COMBINE, (void (CALLBACK *)())tessCombineCB);

	// 处理顶点就直接绘制
	gluTessCallback(ptor, GLU_TESS_VERTEX, (void (CALLBACK *)())glVertex3dv);	

	gluTessProperty(ptor, GLU_TESS_WINDING_RULE, v);
	gluTessProperty(ptor, GLU_TESS_BOUNDARY_ONLY, b);

	glNewList(list, GL_COMPILE);
	gluTessBeginPolygon(ptor, NULL);
	{
		gluTessBeginContour(ptor);
		{
			gluTessVertex(ptor, cquad[0], cquad[0]);
			gluTessVertex(ptor, cquad[1], cquad[1]);
			gluTessVertex(ptor, cquad[2], cquad[2]);
			gluTessVertex(ptor, cquad[3], cquad[3]);
		}
		gluTessEndContour(ptor);
	}
	gluTessEndPolygon(ptor);
	glEndList();


	// 后面换一个回调处理顶点 ：）
	gluTessCallback(ptor, GLU_TESS_VERTEX, (void (CALLBACK *)())tessVertexCB);
	glNewList(list + 1, GL_COMPILE);
	gluTessBeginPolygon(ptor, NULL);
	{
		gluTessBeginContour(ptor);
		{
			gluTessVertex(ptor, hquad[0], hquad[0]);
			gluTessVertex(ptor, hquad[1], hquad[1]);
			gluTessVertex(ptor, hquad[2], hquad[2]);
			gluTessVertex(ptor, hquad[3], hquad[3]);
		}
		gluTessEndContour(ptor);

		gluTessBeginContour(ptor);
		{
			gluTessVertex(ptor, hquad[4], hquad[4]);
			gluTessVertex(ptor, hquad[5], hquad[5]);
			gluTessVertex(ptor, hquad[6], hquad[6]);
			gluTessVertex(ptor, hquad[7], hquad[7]);
		}
		gluTessEndContour(ptor);
	}
	gluTessEndPolygon(ptor);
	glEndList();


	glNewList(list + 2, GL_COMPILE);
	gluTessBeginPolygon(ptor, NULL);
	{
		gluTessBeginContour(ptor);
		{
			gluTessVertex(ptor, fstar[0], fstar[0]);
			gluTessVertex(ptor, fstar[1], fstar[1]);
			gluTessVertex(ptor, fstar[2], fstar[2]);
			gluTessVertex(ptor, fstar[3], fstar[3]);
			gluTessVertex(ptor, fstar[4], fstar[4]);
		}
		gluTessEndContour(ptor);
	}
	gluTessEndPolygon(ptor);
	glEndList();

	gluDeleteTess(ptor);

	return list;
}
