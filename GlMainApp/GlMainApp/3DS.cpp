#include "3DS.hpp"


bool TDSFile::readChunkHead(TDSChunk & chunk)
{
	if (0 == fread(&chunk.id, 1, 2, m_File))
		return false;

	if (0 == fread(&chunk.len, 1, 4, m_File))
		return false;

	return true;
}

bool TDSFile::load(std::wstring pn)
{
	_wfopen_s(&m_File, pn.c_str(), L"rb");
	if (NULL == m_File)
		return false;

	TDSChunk chunk;
	readChunkHead(chunk);
	
	if (MAIN3DS != chunk.id)
	{
		fclose(m_File);
		return false;
	}

	while (readChunkHead(chunk))
	{
		switch (chunk.id)
		{
		case VERSION:
			int ver;
			fread(&ver, 1, 4, m_File);
			if (ver > 0x03)
				return false;
			break;
		case OBJECTINFO:
			read3DS(chunk.len);
			break;

	//	case EDITKEYFRAME:
		default:
		{	
			fseek(m_File, chunk.len - 6, SEEK_CUR);
		}break;

		}
	}
	fclose(m_File);

	return true;
}

void TDSFile::read3DS(TDSDWORD len)
{
	if (len < 6)
		return;

	int cur = ftell(m_File);
	int bar = cur + len - 6;

	while (cur < bar)
	{
		TDSChunk chunk;
		readChunkHead(chunk);
		switch (chunk.id)
		{
		case MESH_VERSION:
			int mver;
			fread(&mver, 1, 4, m_File);
			break;
		case EDIT_MATERIAL:
			fseek(m_File, chunk.len - 6, SEEK_CUR);
			break;
		case EDIT_OBJECT:
			readObject(chunk.len);
			break;
		default:
			fseek(m_File, chunk.len - 6, SEEK_CUR);
			break;
		}
		cur = ftell(m_File);
	}
}

void TDSFile::readObject(TDSDWORD len)
{
	if (len < 6)
		return;

	char name[100];
	memset(name, 0, 100);
	size_t sz = readString(name);

	int cur = ftell(m_File);
	int bar = cur + len - 6 -(sz + 1);
	TDSChunk chunk;
	while (cur < bar)
	{	
		readChunkHead(chunk);
		switch (chunk.id)
		{
		case OBJ_MESH:
			//fseek(m_File, chunk.len - 6, SEEK_CUR);
			readObjMesh(chunk.len);
			break;

		default:
			fseek(m_File, chunk.len - 6, SEEK_CUR);
			break;
		}

		cur = ftell(m_File);
	}
}
void TDSFile::readObjMesh(TDSDWORD len)
{
	if (len < 6)
		return;

	int cur = ftell(m_File);
	int bar = cur + len - 6;
	
	TDSChunk chunk;
	while (cur < bar)
	{
		readChunkHead(chunk);
		switch (chunk.id)
		{
		case OBJ_VERTICES:
			fseek(m_File, chunk.len - 6, SEEK_CUR);
		//	readObjVertex(chunk.len);
			break;
		case OBJ_FACES:
			fseek(m_File, chunk.len - 6, SEEK_CUR);
			//readObjFace(chunk.len);
			break;
		case OBJ_UV:
			fseek(m_File, chunk.len - 6, SEEK_CUR);
			//readObjUV(chunk.len);
			break;
		case OBJ_MATERIAL:
			readObjMat(chunk.len);
			break;
		default:
			fseek(m_File, chunk.len - 6, SEEK_CUR);
			break;
		}

		cur = ftell(m_File);
	}
}

void TDSFile::readObjVertex(TDSDWORD len)
{
	TDSWORD num = 0;
	if (0 == fread(&num, 1, 2, m_File))
		return;

	TDSDWORD readlen = len - 6 - 2;
	TDSBYTE * data = new TDSBYTE[readlen];
	fread(data, 1, readlen, m_File);
	// TODO : 详细顶点信息

	delete[]  data;
}

void TDSFile::readObjFace(TDSDWORD len)
{
	TDSWORD num = 0;
	if (0 == fread(&num, 1, 2, m_File))
		return;

	TDSDWORD readlen = len - 6 - 2;
	TDSBYTE * data = new TDSBYTE[readlen];
	fread(data, 1, readlen, m_File);
	// TODO : 详细面信息

	delete[]  data;
}

void TDSFile::readObjUV(TDSDWORD len)
{
	TDSWORD num = 0;
	if (0 == fread(&num, 1, 2, m_File))
		return;

	TDSDWORD readlen = len - 6 - 2;
	TDSBYTE * data = new TDSBYTE[readlen];
	fread(data, 1, readlen, m_File);
	// TODO : 详细UV信息

	delete[]  data;
}

void TDSFile::readObjMat(TDSDWORD len)
{
	char name[255];
	memset(name, 0, 255);
	size_t sz = readString(name);

	TDSDWORD readlen = len - (sz + 1);
	//TDSBYTE * data = new TDSBYTE[readlen];
	//fread(data, 1, readlen, m_File);
	//// TODO : 详细材质信息

	//delete[]  data;
	fseek(m_File, readlen, SEEK_CUR);
}

size_t TDSFile::readString(char * out)
{
	int index = 0;

	do
	{
		fread(out + index, 1, 1, m_File);
	} while (0 != *(out + index++));
	
	return strlen(out);
}
