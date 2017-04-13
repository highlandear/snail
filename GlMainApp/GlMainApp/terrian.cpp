#include "terrian.hpp"

#include "gmath.hpp"

#include "gdraw.hpp"

Terrain::Terrain(std::wstring hmpn, int w, int h, int s)
	: m_szHeightMapName(hmpn) , m_width(w), m_height(h), m_scale(s)
{
	m_pData = NULL;
}

void Terrain::init()
{
	load();

	TexManager::loadBmpTexrure(L"terrain", L"tex\\terrain.bmp");

	TexManager::loadBmpTexrure(L"box", L"tex\\box.bmp");
}

bool Terrain::load()
{
	m_pData = new unsigned char[m_width * m_height];
	if (NULL == m_pData)
		return false;

	memset(m_pData, 0, m_width * m_height);

	FILE *p;
	_wfopen_s(&p, m_szHeightMapName.c_str(), L"r");

	if (NULL == p) return false;

	fread(m_pData, 1, m_width * m_height, p);

	if (ferror(p))
	{
		fclose(p);
		return false;
	}

	fclose(p);

	return true;
}

/*
	文件中二维数组高度的查询
	row 行
	col 列
*/
int Terrain::find(int row, int col)
{
	if (NULL == m_pData) return 0;

	if (row >= m_width) return 0;
	if (col >= m_height) return 0;

	int index = row * m_width + col;

	return m_pData[index];
}

int Terrain::getAveHeight(float x, float z)
{
	float wx = x / m_scale;
	float wz = z / m_scale;

	int r0 = (int)wz * m_scale;
	int c0 = (int)wx * m_scale;

	int r1 = ((int)wz + 1) * m_scale;
	int c1 = ((int)wx  +1) * m_scale;

	float h00 = floatHeight(find(r0, c0));
	float h01 = floatHeight(find(r0, c1));
	float h10 = floatHeight(find(r1, c0));
	float h11 = floatHeight(find(r1, c1));

	float dx = (x - c0) / m_scale;
	float dz = (z - r0) / m_scale;

	return gmath::bili_interpolation(h00, h01, h10, h11, dx, dz);
}

void Terrain::drawSign()
{
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(0, 190, 0);
	gdraw::drawBall(0.8f);
	glPopMatrix();
}

void Terrain::setTexCoord(float x, float z)
{
	glTexCoord2f((float)x / (float)m_width,
		(float)z / (float) m_height);
}

void Terrain::draw()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	TexManager::attach(L"terrain");


	for (int c = 0; (c + m_scale) < m_width; c += m_scale)
	{
		glBegin(GL_TRIANGLE_STRIP);
		{
			for (int r = 0; (r + m_scale) < m_height; r += m_scale)
			{
				float x0 = (float)c;
				float z0 = (float)r;
				float y0 = floatHeight(find(r, c));

				int r1 = r, c1 = c + m_scale;
				float x1 = (float)c1;
				float z1 = (float)r1;
				float y1 = floatHeight(find(r1, c1));

				setTexCoord(x0, z0);
				glVertex3f(x0, y0, z0);

				setTexCoord(x1, z1);
				glVertex3f(x1, y1, z1);
			}			
		}
		glEnd();
	}
}

void Terrain::drawGridPoints()
{
	glColor3f(1.0f, 0.0f, 0.0f);

	glPointSize(5.0f);
	glBegin(GL_POINTS);
	{
		for (int r = 0; r < m_height; r+=m_scale)
		{
			for (int c = 0; c < m_width; c+= m_scale)
			{
				float z = (float)r;
				float x = (float)c;
				float y = floatHeight(find(r, c));

				glVertex3f(x, y, z);
			}
		}
	}
	glEnd();
}

void Terrain::drawPoints()
{
	glColor3f(1.0f, 1.0f, 1.0f);

	glPointSize(1.0f);
	glBegin(GL_POINTS);
	{
		for (int r = 0; r < m_width; r++)
		{
			for (int c = 0; c < m_height; c++)
			{
				float z = (float) r;
				float x = (float) c;
				float y = floatHeight(find(r, c));

				glVertex3f(x, y, z);
			}
		}
	}
	glEnd();
}

void Terrain::drawBox(float x, float z)
{
	TexManager::attach(L"box");

	float y = getAveHeight(x, z);

	gdraw::drawCube(x, y, z, 10.0f);
}