#include "illuminant.hpp"


GLight LightManager::lights[8];

void LightManager::onDefault()
{
	GLfloat lam[] = { 1.0f, 1.0f, 1.0f, 1.0f };	// ���������
	GLfloat ld[] = { 1.0f, 1.0f, 1.0f, 1.0f };	// ��������
	GLfloat ls[] = { 1.0f, 1.0f, 1.0f, 1.0f };	// ��������
	GLfloat lp[] = { 0.0f, 0.0f, 0.0f, 1.0f };	// ��Դλ��
	GLfloat lat[] = { 0.03f };

	on(0);

	lights[0].setAmbientV(lam);
	lights[0].setAttenuationV(lat);
	lights[0].setDiffuseV(ld);
	lights[0].setSpecularV(ls);
	lights[0].setPosV(lp);
}
