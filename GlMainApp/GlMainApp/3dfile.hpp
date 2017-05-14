#pragma once
#include"3dmodel.hpp"

class ModelFile
{
public:

	virtual bool load(std::wstring pn) = 0;

protected:

	FILE * m_File;
};