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
	
	if (ID_3DS_MAIN != chunk.id)
	{
		fclose(m_File);
		return false;
	}

	while (readChunkHead(chunk))
	{
		switch (chunk.id)
		{
		case ID_3DS_VER:
			int ver;
			fread(&ver, 1, 4, m_File);
			if (ver > 0x03)
				return false;
			break;
		case ID_3DS_OBJ:
			read3DS(chunk.len - 6);
			break;

		case ID_3DS_KEYFRAME:
		default:
		{	
			fseek(m_File, chunk.len - 6, SEEK_CUR);
		}break;

		}
	}
	fclose(m_File);

	return true;
}

void TDSFile::read3DS(int len)
{
	if (len < 0)
		return;

	int cur = ftell(m_File);
	int bar = cur + len;

	while (cur < bar)
	{
		TDSChunk chunk;
		readChunkHead(chunk);
		switch (chunk.id)
		{
		case ID_OBJ_MESHVER:
			int mver;
			fread(&mver, 1, 4, m_File);
			break;
		case ID_OBJ_MAT:
			readMaterial(chunk.len - 6);
			break;
		case ID_OBJ_INFO:
			readObject(chunk.len - 6);
			break;
		default:
			fseek(m_File, chunk.len - 6, SEEK_CUR);
			break;
		}
		cur = ftell(m_File);
	}
}

void TDSFile::readMaterial(int len)
{
	if (len < 0)
		return;

	TDSMaterial tdsmat;

	int cur = ftell(m_File);
	int bar = cur + len;
	TDSChunk chunk;
	while (cur < bar)
	{
		readChunkHead(chunk);
		switch (chunk.id)
		{
		case ID_MAT_NAME:
			char name[256];
			fread(name, 1, chunk.len - 6, m_File);
			tdsmat.name = std::string(name);
			break;
		case ID_MAT_COLOR:
			readMatColor(chunk.len - 6, tdsmat);
			break;
		case ID_MAT_MAP:
			readMatMap(chunk.len - 6, tdsmat);
			break;

		default:
			fseek(m_File, chunk.len -6, SEEK_CUR);
			break;
		}
		cur = ftell(m_File);
	}

	m_Model.mats.push_back(tdsmat);
}
void TDSFile::readMatColor(int len, TDSMaterial & tdsmat)
{
	if(len < 0)
		return;

	TDSChunk chunk;
	readChunkHead(chunk);
	if (ID_COLOR_24 == chunk.id)
	{
		fread(tdsmat.color, 1, chunk.len - 6, m_File);
	}
	else
	{
		fseek(m_File, len - 6, SEEK_CUR);
	}

}

void TDSFile::readMatMap(int len, TDSMaterial & tdsmat)
{
	if (len < 0)
		return;
	
	int cur = ftell(m_File);
	int bar = cur + len;
	while (cur < bar)
	{
		TDSChunk chunk;
		readChunkHead(chunk);
		switch (chunk.id)
		{
		case ID_MAP_FILE:
			char fname[256];
			fread(fname, 1, chunk.len - 6, m_File);
			tdsmat.filename = std::string(fname);
			break;
		default:
			fseek(m_File, chunk.len - 6, SEEK_CUR);
			break;
		}
		
		cur = ftell(m_File);
	}
}

void TDSFile::readObject(int len)
{
	if (len < 0)
		return;


	char name[128];
	memset(name, 0, 128);
	size_t sz = readString(name);
	TDSObject tdsobj;
	tdsobj.name = std::string(name);

	int cur = ftell(m_File);
	int bar = cur + len;
	bar -= (sz + 1);

	TDSChunk chunk;
	while (cur < bar)
	{	
		readChunkHead(chunk);
		switch (chunk.id)
		{
		case ID_INFO_MESH:
			readObjMesh(chunk.len - 6, tdsobj);
			break;

		default:
			fseek(m_File, chunk.len - 6, SEEK_CUR);
			break;
		}

		cur = ftell(m_File);
	}

	m_Model.objs.push_back(tdsobj);
}
void TDSFile::readObjMesh(int len, TDSObject & tdsobj)
{
	if (len < 0)
		return;

	int cur = ftell(m_File);
	int bar = cur + len;
	
	TDSChunk chunk;
	while (cur < bar)
	{	
		readChunkHead(chunk);
		switch (chunk.id)
		{
		case ID_MESH_VERTICES:
			readObjVertex(chunk.len - 6, tdsobj);
			break;
		case ID_MESH_FACES:
			readObjFace(chunk.len - 6, tdsobj);
			break;
		case ID_MESH_TEX:
			readObjUV(chunk.len - 6, tdsobj);
			break;
		default:
			fseek(m_File, chunk.len - 6, SEEK_CUR);
			break;
		}
		
		cur = ftell(m_File);
	}
}

void TDSFile::readObjVertex(int len, TDSObject & tdsobj)
{
	TDSWORD num = 0;
	if (0 == fread(&num, 1, 2, m_File))
		return;

	TDSDWORD readlen = len - 2;
	TDSBYTE * data = new TDSBYTE[readlen];
	fread(data, 1, readlen, m_File);

	Vector3D * v = (Vector3D *) data;
	for (int i = 0; i < num; i++)
	{
		float ty = v[i].y;		
		v[i].y = v[i].z;	//设置Y轴的值等于Z轴的值		
		v[i].z = - ty;		//设置Z轴的值等于-Y轴的值

		tdsobj.vertices.push_back(v[i]);
	}

	delete[]  data;
}

void TDSFile::readObjFace(int len, TDSObject & tdsobj)
{
	TDSWORD num = 0;
	if (0 == fread(&num, 1, 2, m_File))
		return;

	// 读顶点索引
	unsigned short index = 0;
	for (int i = 0; i < num; i++)
	{
		TDSFace face;
		for (int j = 0; j < 4; j++)
		{			
			fread(&index, 1, 2, m_File);
			if (j < 3)
				face.vertex_index[j] = index;
		}
		
		tdsobj.faces.push_back(face);
	}

	int cur = ftell(m_File);
	int bar = cur + len;
	bar -= 2;
	bar -= num * 8;

	// 读子块
	TDSChunk chunk;
	while (cur < bar)
	{
		readChunkHead(chunk);
		switch (chunk.id)
		{
		case ID_MESH_MAT:
		{
			readObjMat(chunk.len - 6, tdsobj);
		}break;
		case ID_MESH_SMOOTH:
		{
			fseek(m_File, chunk.len - 6, SEEK_CUR);
		}break;
		default:
		{
			fseek(m_File, chunk.len - 6, SEEK_CUR);
		}break;
		}

		cur = ftell(m_File);
	}
}

void TDSFile::readObjUV(int len, TDSObject & tdsobj)
{
	TDSWORD num = 0;
	if (0 == fread(&num, 1, 2, m_File))
		return;

	TDSDWORD readlen = len- 2;
	TDSBYTE * data = new TDSBYTE[readlen];
	fread(data, 1, readlen, m_File);
	Vector2D * v = (Vector2D *)data;
	for (int i = 0; i < num; i++)
	{
		tdsobj.texuvs.push_back(v[i]);
	}

	delete[]  data;
}

void TDSFile::readObjMat(int len, TDSObject & tdsobj)
{	
	char mname[255];
	memset(mname, 0, 255);
	size_t sz = readString(mname);

	TDSDWORD readlen = len;
	readlen -= (sz + 1);
	TDSBYTE * data = new TDSBYTE[readlen];
	fread(data, 1, readlen, m_File);
	// 详细材质信息 nothing to do 

	delete[]  data;
	tdsobj.texname = "";

	for (TDSMaterial & t : m_Model.mats)
	{
		if (t.name == mname)
		{
			tdsobj.texname = t.filename;
		}
	}
	
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
