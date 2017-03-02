#include "gout.hpp"
#include <gl/GL.h>
#include <sstream>

int gout::fontSize = 18;

HFONT gout::sFont = CreateFont(
	fontSize,					// ����߶�
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


void gout::split(std::wstring str, std::vector<std::wstring> & v, std::wstring sep)
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

void gout::xprint(std::wstring str, float x, float y, float z)
{
	HDC hdc = wglGetCurrentDC();

	if (NULL == hdc) return;

	SelectObject(hdc, sFont);

	glRasterPos3f(x, y, z);
	
	GLuint list = glGenLists(1);
	for (int i = 0; i < str.size(); i++)
	{
		wglUseFontBitmaps(hdc, str[i], 1, list);
		glCallList(list);
	}
	glDeleteLists(list, 1);
}

void gout::wprint(std::wstring str, float x, float y, float z)
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

/**
	λ�� + ���
*/
void gout::wprint3D(std::wstring str, float x, float y, float z, float depth)
{
	HDC hdc = wglGetCurrentDC();
	
	GLYPHMETRICSFLOAT pgmf[1];

	if (NULL == hdc) return;

	SelectObject(hdc, sFont);

	glRasterPos3f(x, y, z);
	
	for (int i = 0; i < str.size(); i++)
	{
		GLuint list = glGenLists(1);
		wglUseFontOutlines(hdc, str[i], 1, list, 0.0f, depth, WGL_FONT_POLYGONS, pgmf);
		glCallList(list);
		glDeleteLists(list, 1);
	}
}

template <typename T>
std::wstring gout::toString(T t)
{
	std::wostringstream ws;
	ws << t;

	return ws.str();
}

std::wstring gout::wstringPos(float x, float y, float z)
{
	std::wostringstream ws;
	ws << "(" << x << "," << y << "," << z << ")";

	return ws.str();
}

std::wstring gout::wstringPos(float x, float y)
{
	std::wostringstream ws;
	ws << "(" << x << "," << y << ")";

	return ws.str();
}
