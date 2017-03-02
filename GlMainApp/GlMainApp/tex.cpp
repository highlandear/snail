#include "Tex.hpp"
#include <stdio.h>

std::unordered_map<std::wstring, unsigned int> TexManager::tmap;

GLfloat RawTex::simple_data[] =
{
	//	红  洋
	//	绿  蓝
	1.0f, 0.0f, 1.0f,1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f
};

bool RawTex::load()
{
	unsigned int id;
	glGenTextures(1, &id);
	setTextureID(id);

	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, m_pData);

	return true;
}

bool BmpTex::load()
{
	FILE * p;
	_wfopen_s(&p, m_szPathName.c_str(), L"r");

	if (NULL == p)
		return false;

	BITMAPINFOHEADER info_header;
	BITMAPFILEHEADER file_header;

	unsigned char color = 0;		// 用于将BGR转换为RGB

	fread(&file_header, sizeof(BITMAPFILEHEADER), 1, p);
	if (BITMAP_FLAG != file_header.bfType)
		return false;

	fread(&info_header, sizeof(BITMAPINFOHEADER), 1, p);
	m_nWith = info_header.biWidth;
	m_nHight = info_header.biHeight;

	if (0 == info_header.biSizeImage)
		info_header.biSizeImage = info_header.biWidth *	info_header.biHeight * 3;


	fseek(p, file_header.bfOffBits, SEEK_SET);

	m_pData = new unsigned char[info_header.biSizeImage];
	if (NULL == m_pData)
	{
		fclose(p);
		return false;
	}

	fread(m_pData, 1, info_header.biSizeImage, p);

	for (size_t i = 0; i < info_header.biSizeImage; i += 3)
	{
		color = m_pData[i];
		m_pData[i] = m_pData[i + 2];
		m_pData[i + 2] = color;
	}

	fclose(p);

	unsigned int id;
	glGenTextures(1, &id);
	setTextureID(id);

	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_nWith, m_nHight, 0, GL_RGB, GL_UNSIGNED_BYTE, m_pData);

	return true;
}

void TexManager::put(Tex & t)
{
	tmap[t.getName()] = t.getTextureID();
}

unsigned int TexManager:: get(std::wstring n)
{
	TMAP::const_iterator it = tmap.find(n);
	if (it == tmap.end())
		return 0;

	return it->second;
}

bool TexManager::attach(std::wstring n)
{
	if (n == L"leaf")
	{

	}
	unsigned tid = get(n);
	if (0 == tid)
		return false;

	glBindTexture(GL_TEXTURE_2D, tid);
	glEnable(GL_TEXTURE_2D);

	return true;
}

void TexManager::detachAll()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	//glDisable(GL_TEXTURE_GEN_S);
	//glDisable(GL_TEXTURE_GEN_T);
}

void TexManager::clear()
{
	detachAll();
	tmap.clear();
	glDisable(GL_TEXTURE_2D);
}

void TexManager::loadBmpTexrure(std::wstring name, std::wstring fpn)
{
		BmpTex t(name, fpn);
		t.load();		
		put(t);
}

void TexManager::loadRawTexrure(std::wstring name)
{
	RawTex t(name);
	t.load();
	put(t);
}

