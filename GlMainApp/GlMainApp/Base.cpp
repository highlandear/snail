#include "Base.hpp"
#include <gl/glut.h>
#include <vector>

namespace gdraw
{
	void drawBall(float radius)
	{
		glutSolidSphere(radius, 50, 50);
	}

	void drawBall(float radius, float x, float y, float z)
	{
		glPushMatrix();
		{
			glTranslatef(x, y, z);
			glutSolidSphere(radius, 50, 50);
		}
		glPopMatrix();
	}

	void drawCube(float size)
	{
		glutSolidCube(size);
	}

	void drawCube(float size, float x, float y, float z)
	{
		glPushMatrix();
		{
			glTranslatef(x, y, z);
			glutSolidCube(size);
		}
		glPopMatrix();
	}

	void drawTeaPot(float size)
	{
		glutSolidTeapot(size);
	}

	void drawTeaPot(float size, float x, float y, float z)
	{
		glPushMatrix();
		{
			glTranslatef(x, y, z);
			glutSolidTeapot(size);
		}
		glPopMatrix();
	}

	void print(float x, float y, float z, const char * str)
	{
		glRasterPos3f(x, y, z);
		for (int i = 0; i < strlen(str); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *(str + i));
	}

	void wprint(float x, float y, float z, const wchar_t *str)
	{
		glRasterPos3f(x, y, z);
		for (int i = 0; i < wcslen(str); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *(str + i));
	}
}

void split(std::wstring str, std::vector<std::wstring> & v, std::wstring sep = L" ")
{
	if (str.empty()) return;

	std::wstring item;
	std::wstring::size_type pos_begin = str.find_first_not_of(sep);
	std::wstring::size_type comma_pos = 0;

	while (pos_begin != std::wstring::npos)
	{
		comma_pos = str.find(sep, pos_begin);
		if (comma_pos != std::wstring::npos)
		{
			item = str.substr(pos_begin, comma_pos - pos_begin);
			pos_begin = comma_pos + sep.length();
		}
		else
		{
			item = str.substr(pos_begin);
			pos_begin = comma_pos;
		}

		if (!item.empty())
		{
			v.push_back(item);
			item.clear();
		}
	}
}

namespace tout
{
	static HDC hdc;

	HFONT sFont = CreateFont(
		18,							// ����߶�
		0,							// ������
		0,							// �������ת�Ƕ�
		0,							// ������ߵ���ת�Ƕ�Orientation Angle
		FW_BOLD,					// ���������
		FALSE,						// �Ƿ�ʹ��б��
		FALSE,						// �Ƿ�ʹ���»���
		FALSE,						// �Ƿ�ʹ��ɾ����
		GB2312_CHARSET,				// �����ַ���
		OUT_TT_PRECIS,				// �������
		CLIP_DEFAULT_PRECIS,		// �ü�����
		ANTIALIASED_QUALITY,		// �������
		FF_DONTCARE | DEFAULT_PITCH,// Family And Pitch
		L"����");					// ��������
	
	
	//void xprint(wchar_t * wstr, float x, float y, float z)
	//{
	//	hdc = wglGetCurrentDC();

	//	if (NULL == hdc) return;

	//	SelectObject(hdc, sFont);

	//	glRasterPos3f(x, y, z);

	//	GLuint list = glGenLists(1);
	//	for (int i = 0; i<wcslen(wstr); i++)
	//	{
	//		wglUseFontBitmaps(hdc, wstr[i], 1, list);
	//		glCallList(list);
	//	}
	//	glDeleteLists(list, 1);
	//}

	void xprint(std::wstring str, float x, float y, float z)
	{
		hdc = wglGetCurrentDC();

		if (NULL == hdc) return;

		SelectObject(hdc, sFont);

		glRasterPos3f(x, y, z);

		GLuint list = glGenLists(1);
		for (int i = 0; i<str.size(); i++)
		{
			wglUseFontBitmaps(hdc, str[i], 1, list);
			glCallList(list);
		}
		glDeleteLists(list, 1);
	}

	void wprint(std::wstring str, float x, float y, float z)
	{
		std::vector<std::wstring> v;
		split(str, v, L"\n");

		float y0 = y;
		for (std::wstring s : v)
		{
			xprint(s, x, y0, z);
			y0 -= 0.3;
		}
	}

}