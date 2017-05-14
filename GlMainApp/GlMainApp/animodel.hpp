#pragma once

#include "3dmodel.hpp"
#include "keyStatus.hpp"

/*
动作信息
*/
struct AniFrameInfo
{
	std::string name;			// 帧的名称
	int startFrame;				// 开始帧
	int endFrame;				// 结束帧
};

struct AniModel : public _3DModel
{
	void draw();
	void update();

	bool isKeyDown(UINT k) { return KeyStatus::isKeyDown(k); }

	int m_curAnim;			// 当前动作
	int m_curFrame;			// 动作的当前帧

	std::vector<AniFrameInfo> animations;
};