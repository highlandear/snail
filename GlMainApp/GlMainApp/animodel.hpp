#pragma once

#include "3dmodel.hpp"
#include "keyStatus.hpp"

/*
������Ϣ
*/
struct AniFrameInfo
{
	std::string name;			// ֡������
	int startFrame;				// ��ʼ֡
	int endFrame;				// ����֡
};

struct AniModel : public _3DModel
{
	void draw();
	void update();

	bool isKeyDown(UINT k) { return KeyStatus::isKeyDown(k); }

	int m_curAnim;			// ��ǰ����
	int m_curFrame;			// �����ĵ�ǰ֡

	std::vector<AniFrameInfo> animations;
};