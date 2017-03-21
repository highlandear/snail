// Showme.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "gmatrix.hpp"
#include <iostream>
#include"xvector.hpp"


int main()
{
	int a[] = { 1, 2, 3, 4 ,5, 6};
	int b[] = { 2, 3, 4, 5, 6};
	GVector<int> va = GVector<int>(a, 6);
	GVector<int> vb = GVector<int>(b, 5);

	std::wcout << va.toString() << std::endl;
	std::wcout << vb.toString() << std::endl;

	GVector<int> sum = va + vb;
	std::wcout << sum.toString() << std::endl;

}

