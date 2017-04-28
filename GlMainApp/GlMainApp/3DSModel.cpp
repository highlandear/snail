#include "3DSModel.hpp"
#include <fstream>
#include <windows.h>
bool TDSModel::load(std::wstring pn)
{
	TDSFile tf;
	return tf.load(pn);

}

void TDSModel::loadObj(unsigned char * data, size_t size)
{

}
void TDSModel::loadMat(unsigned char * data, size_t size)
{

}