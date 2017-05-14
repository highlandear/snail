#include "animodel.hpp"
#include "tex.hpp"
#include "timer.hpp"

void AniModel::update()
{
	if (isKeyDown(VK_SPACE))
	{
		m_curAnim = (m_curAnim + 1) % animations.size();
	}

}

void AniModel::draw()
{
	if (objs.empty())
		return;

	AniFrameInfo & curAnimation = animations[m_curAnim];

	int nextFrame = (m_curFrame + 1) % curAnimation.endFrame;

	if (0 == nextFrame)
	{
		nextFrame = curAnimation.startFrame;
	}
		

	MObject & firstFrameObj = objs[0];				// ��֡����
	MObject & curFrameObj = objs[m_curFrame];		// ��ǰ֡����
	MObject & nextFrameObj = objs[nextFrame];		// ��һ֡����

	if(helper::getElapse(100))
		m_curFrame = nextFrame;


	glPushAttrib(GL_CURRENT_BIT);
	glBegin(GL_TRIANGLES);
	for (ModelFace & f : firstFrameObj.faces)
	{
		for (int i = 0; i < 3; i++)
		{
			int ver_index = f.vertex_index[i];
			int tex_index = f.coord_index[i];

			glTexCoord2f(firstFrameObj.texuvs[tex_index].x, firstFrameObj.texuvs[tex_index].y);

			Vector3D & v1 = curFrameObj.vertices[ver_index];
			glVertex3f(v1.x, v1.y, v1.z);
		}
	}

	glEnd();
	glPopAttrib();
}