#include "vector3D.hpp"

/*
	���� �� ����
*/
Vector3D Vector3D::rihgtProduct(float m[3][3])
{
	Vector3D ret = Vector3D();
	ret.x = m[0][0] * x + m[0][1] * y + m[0][2] * z;
	ret.y = m[1][0] * x + m[1][1] * y + m[1][2] * z;
	ret.z = m[2][0] * x + m[2][1] * y + m[2][2] * z;

	return ret;
}

/*
	�أ�Ax, Ay, Az�� ������ת theta ����
*/
Vector3D Vector3D::roll(float theta, float Ax, float Ay, float Az)
{
	float c = cosf(theta);
	float s = sinf(theta);
	
	// ��ת ����
	float mat[3][3] = {
		{ c + (1-c)*Ax*Ax,  (1 - c)*Ax*Ay - s*Az,  (1 - c)*Ax*Az + s*Ay},
		{ (1-c)*Ax*Ay+s*Az,  c+(1-c)*Ay*Ay,        (1-c)*Ay*Az-s*Ax },
		{ (1-c)*Ax*Az-s*Ay,  (1-c)*Ay*Az+s*Ax,       c+(1-c)*Az*Az}
	};

	return rihgtProduct(mat);
}