#include "3dmodel.hpp"
#include <Windows.h>
#include <gl/GL.h>
#include "tex.hpp"

void _3DModel::init()
{
	loadTex();
}

void _3DModel::loadTex()
{
	for (MMaterial & t : mats)
	{
		if (t.filename.empty())
			continue;

		TexManager::loadBmpTexrure(t.filename, t.filename);
	}
}

void _3DModel::draw()
{
	glPushAttrib(GL_CURRENT_BIT);

	for (MObject & o : objs)
	{
		glColor3f(1.0, 1.0f, 1.0f);

		if (!o.texname.empty())
		{
			TexManager::attach(o.texname);
		}
		glBegin(GL_TRIANGLES);
		{
			for (ModelFace & f : o.faces)
			{
				for (int i = 0; i < 3; i++)
				{
					int index = f.vertex_index[i];
					
					glTexCoord2f(o.texuvs[index].x, o.texuvs[index].y);

					glVertex3f(o.vertices[index].x, o.vertices[index].y, o.vertices[index].z);
				}
			}
		}
		glEnd();
	}

	glPopAttrib();
}

/*
	这是一个对比效果，最简单的方式画一个模型
	以格子的方式画出模型的框架
*/
void _3DModel::drawHollow()
{
	glPushAttrib(GL_CURRENT_BIT);

	for (MObject & o : objs)
	{
		glColor3f(1.0, 0.0f, 0.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_TRIANGLES);
		{
			for (ModelFace & f : o.faces)
			{
				for (int i = 0; i < 3; i++)
				{
					int index = f.vertex_index[i];
					glVertex3f(o.vertices[index].x, o.vertices[index].y, o.vertices[index].z);
				}
			}
		}
		glEnd();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glPopAttrib();
}