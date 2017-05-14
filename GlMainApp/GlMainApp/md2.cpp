#include "md2.hpp"
#include "strhelper.hpp"

std::string MD2File::readSkinName()
{
	if (NULL == m_File)
		return "";

	char name[256];

	fseek(m_File, m_Header.offsetSkins, SEEK_SET);
	fread(name, 1, m_Header.numSkins, m_File);

	return name;
}

int MD2File::readUVs()
{
	UV * p = new UV[m_Header.numTexCoords];
	fseek(m_File, m_Header.offsetTexCoords, SEEK_SET);
	fread(p, sizeof(UV), m_Header.numTexCoords, m_File);
	m_uvs.insert(m_uvs.begin(), p, p + m_Header.numTexCoords);
	delete[] p;
	return m_uvs.size();
}

int MD2File::readFaces()
{
	ModelFace * p = new ModelFace[m_Header.numTriangles];
	fseek(m_File, m_Header.offsetTriangles, SEEK_SET);
	fread(p, sizeof(ModelFace), m_Header.numTriangles, m_File);

	m_faces.insert(m_faces.begin(), p, p + m_Header.numTriangles);
	delete[] p;

	return m_faces.size();
}

int MD2File::readFrames()
{
	fseek(m_File, m_Header.offsetFrames, SEEK_SET);

	for (int i = 0; i < m_Header.numFrames; i++)
	{
		MD2KeyFrame kf;
		unsigned char * p = new unsigned char[m_Header.frameSize];
		fread(p, 1, m_Header.frameSize, m_File);

		MD2Frame * pf = (MD2Frame *)p;
		kf.name = pf->name;

		for (int j = 0; j < m_Header.numVertices; j++)
		{
			MD2Triangle tr;
			tr.vertex[0] = pf->fvertex[j].vertex[0] * pf->scale[0] + pf->translate[0];
			tr.vertex[1] = pf->fvertex[j].vertex[2] * pf->scale[2] + pf->translate[2];
			tr.vertex[2] = pf->fvertex[j].vertex[1] * pf->scale[1] + pf->translate[1];
			
			tr.vertex[2] *= -1;
			
			kf.triangles.push_back(tr);
		}

		delete[] p;

		m_kfs.push_back(kf);
	}

	return m_kfs.size();
}

void MD2File::addModelAnimation()
{
	std::string lastFrameName = "";

	for (int i=0; i<m_kfs.size(); i++)
	{
		MD2KeyFrame & kf = m_kfs[i];
		AniFrameInfo afi;

		std::string frameName = kf.name;
		int fnum = helper::getTailNum2(frameName);

		if (lastFrameName != frameName  ||  i == (m_Header.numFrames -1))
		{
			if (! lastFrameName.empty())
			{
				afi.name = lastFrameName;
				afi.endFrame = i;

				m_Model.animations.push_back(afi);
			}
			afi.startFrame = fnum + i - 1;
		}
		lastFrameName = frameName;
	}
}

// 初始化对象模型
void MD2File::addModelObjects()
{
	for(int i = 0; i< m_kfs.size(); i++)
	{
		MD2KeyFrame & kf = m_kfs[i];
		MObject obj;
		for (MD2Triangle & t : kf.triangles)
		{
			Vector3D v(t.vertex[0], t.vertex[1], t.vertex[2]);
			obj.vertices.push_back(v);
		}

		
		// 其它帧，只存顶点信息
		if (i > 0)
		{
			m_Model.objs.push_back(obj);
			continue;
		}
		
		// 第1帧，存面，纹理等其他信息
		for(UV & uv : m_uvs)
		{
			Vector2D v(uv.u / float(m_Header.skinWidth),1 - uv.v / float(m_Header.skinHeight));
			obj.texuvs.push_back(v);
		}
		
		obj.faces = m_faces;
		
		m_Model.objs.push_back(obj);
	}
}

void MD2File::loadTex(std::string tfname)
{
	if (tfname.empty())
		return;
	MMaterial m;
	m.filename = tfname;
	m_Model.mats.push_back(m);
}

bool MD2File::load(std::wstring pn)
{
	_wfopen_s(&m_File, pn.c_str(), L"rb");
	if (NULL == m_File)
		return false;

	fread(&m_Header, 1, sizeof(m_Header), m_File);
	if (8 != m_Header.version)
		return false;

//	std::string skinname = readSkinName();

	readUVs();

	readFaces();
	
	readFrames();

	addModelAnimation();

	addModelObjects();
	
	fclose(m_File);

	return true;
}

