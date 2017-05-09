#include "Tex.hpp"
#include <stdio.h>

typename TexManager::TMAP TexManager::tmap;

GLfloat RawTex::simple_data[] =
{
	//	��  ��
	//	��  ��
	1.0f, 0.0f, 1.0f,1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f
};

int Tex::setTexture()
{
	if (NULL == m_pData)
		return 0;

	unsigned int id;
	glGenTextures(1, &id);
	setTextureID(id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, m_nWith, m_nHight, m_uType,	GL_UNSIGNED_BYTE, m_pData);

	return (int)id;
}



bool BmpTex::load(std::wstring pn)
{
	FILE * p;
	_wfopen_s(&p, pn.c_str(), L"r");

	if (NULL == p)
		return false;

	BITMAPINFOHEADER info_header;
	BITMAPFILEHEADER file_header;

	unsigned char color = 0;		// ���ڽ�BGRת��ΪRGB

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
	return true;
}

bool BmpTex::load(std::string pn)
{
	FILE * p;
	fopen_s(&p, pn.c_str(), "r");

	if (NULL == p)
		return false;

	BITMAPINFOHEADER info_header;
	BITMAPFILEHEADER file_header;

	unsigned char color = 0;		// ���ڽ�BGRת��ΪRGB

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
	return true;
}

bool TgaTex::load(std::wstring pn)
{
	FILE *p;
	_wfopen_s(&p, pn.c_str(), L"r");

	if (NULL == p) return false;

	unsigned char tempColor;				// ���ڽ�����ɫ����
	unsigned char bitCount;					 // ÿ���ص�bitλ��
	int colorMode;							// ��ɫģʽ
	long tgaSize;							// TGA�ļ���С
	unsigned char unCompressHeader[12] = 
	{ 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // δѹ��TGA�ļ�ͷ
	unsigned char tgaHeader[12];			// �ļ�ͷ
	unsigned char header[6];

	// ��ȡ�ļ�ͷǰ12���ֽ�
	fread(tgaHeader, 1, sizeof(tgaHeader), p);

	// �Ƚ��ļ��Ƿ�Ϊδѹ���ļ�
	if (memcmp(unCompressHeader, tgaHeader, sizeof(unCompressHeader)) != 0)
	{
		fclose(p);
		return false;
	}

	// ��ȡ6���ֽ�
	fread(header, 1, sizeof(header), p);
	
	// ����ͼ��Ŀ�Ⱥ͸߶�
	m_nWith = header[1] * 256 + header[0];
	m_nHight = header[3] * 256 + header[2];

	// ��ȡÿ���ص�bitλ��
	bitCount = header[4];

	//��������ɫģʽ��ͼ���С
	colorMode = bitCount / 8;
	tgaSize = m_nWith * m_nHight * colorMode;

	// �����ڴ�
	m_pData = new unsigned char[sizeof(unsigned char) * tgaSize];

	// ��ȡ����
	fread(m_pData, sizeof(unsigned char), tgaSize, p);

	// ��BGA��ʽת��ΪRGA��ʽ
	for (long index = 0; index < tgaSize; index += colorMode)
	{
		tempColor = m_pData[index];
		m_pData[index] = m_pData[index + 2];
		m_pData[index + 2] = tempColor;
	}

	fclose(p);

	m_uType = (colorMode == 3) ? GL_RGB : GL_RGBA;
	return true;
}

bool TgaTex::load(std::string pn)
{
	FILE *p;
	fopen_s(&p, pn.c_str(), "r");

	if (NULL == p) return false;

	unsigned char tempColor;				// ���ڽ�����ɫ����
	unsigned char bitCount;					 // ÿ���ص�bitλ��
	int colorMode;							// ��ɫģʽ
	long tgaSize;							// TGA�ļ���С
	unsigned char unCompressHeader[12] =
	{ 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // δѹ��TGA�ļ�ͷ
	unsigned char tgaHeader[12];			// �ļ�ͷ
	unsigned char header[6];

	// ��ȡ�ļ�ͷǰ12���ֽ�
	fread(tgaHeader, 1, sizeof(tgaHeader), p);

	// �Ƚ��ļ��Ƿ�Ϊδѹ���ļ�
	if (memcmp(unCompressHeader, tgaHeader, sizeof(unCompressHeader)) != 0)
	{
		fclose(p);
		return false;
	}

	// ��ȡ6���ֽ�
	fread(header, 1, sizeof(header), p);

	// ����ͼ��Ŀ�Ⱥ͸߶�
	m_nWith = header[1] * 256 + header[0];
	m_nHight = header[3] * 256 + header[2];

	// ��ȡÿ���ص�bitλ��
	bitCount = header[4];

	//��������ɫģʽ��ͼ���С
	colorMode = bitCount / 8;
	tgaSize = m_nWith * m_nHight * colorMode;

	// �����ڴ�
	m_pData = new unsigned char[sizeof(unsigned char) * tgaSize];

	// ��ȡ����
	fread(m_pData, sizeof(unsigned char), tgaSize, p);

	// ��BGA��ʽת��ΪRGA��ʽ
	for (long index = 0; index < tgaSize; index += colorMode)
	{
		tempColor = m_pData[index];
		m_pData[index] = m_pData[index + 2];
		m_pData[index + 2] = tempColor;
	}

	fclose(p);

	m_uType = (colorMode == 3) ? GL_RGB : GL_RGBA;
	return true;
}



unsigned int TexManager:: get(std::string n)
{
	TMAP::const_iterator it = tmap.find(n);
	if (it == tmap.end())
		return 0;

	return it->second;
}

bool TexManager::attach(std::string n)
{
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
}

void TexManager::clear()
{
	detachAll();
	tmap.clear();
	glDisable(GL_TEXTURE_2D);
}

void TexManager::loadBmpTexrure(std::string name, std::string fpn)
{
		BmpTex t;
		t.load(fpn);
		put(name, t.setTexture());
}

void TexManager::loadTgaTexrure(std::string name, std::string fpn)
{
	TgaTex t;
	t.load(fpn);
	put(name, t.setTexture());
}
