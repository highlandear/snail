
#include "stdafx.h"
#include <iostream>


int fac(int n)
{
	if (0 == n)
		return 1;

	return  n * fac(n - 1);
}




int getTailNum(std::string str)
{
	std::string sub = "";
	for (int i = str.size() - 1; i >= 0; i--)
	{
		char c = str.at(i);
		if (isdigit(c))
			sub = c + sub;
		else
			break;
	}
	if (sub.empty())
		return 0;

	return atoi(sub.c_str());
}

std::string cutTailNum(std::string str)
{

	for (int i = str.size() - 1; i >= 0; i--)
	{
		char c = str.at(i);
		if (! isdigit(c))
		{
			return str.substr(0, i+1);
			break;
		}
	}

	return "";	
}


int getTailNum2(std::string & str)
{
	int num = 0;
	for (unsigned int j = 0; j < str.length(); j++)
	{
		if (isdigit(str[j]) && j >= str.length() - 2)
		{
			num = atoi(&str[j]);

			str.erase(j, str.length() - j);
			break;
		}
	}
	return num;
}

int compare(int a, int b)
{
	if (a < b)
		return -1;

	if (a > b)
		return 1;

	return 0;
}

int add(int a, int b)
{
	int sum = a + b;

	return sum;
}

char * getStr()
{
	return "abcd";
}

char * getStr_2()
{
	char str[100];
	memcpy(str, "stack region", 5);
	return str;
}

char * getStr_3()
{
	char * str = new char[1024 * 1024 * 1024];
	memcpy(str, "heap region", 12);
	return str;
}

void test()
{
	char * str2 = getStr_2();
	std::cout << str2 << std::endl;

	char * str3 = getStr_3();

	std::cout << str3 << std::endl;

	delete[] str3;
}
typedef unsigned char cbyte;

int max = 65535;
const float PI = 3.1415926;
void main()
{
	int sum = add(3, 4);
	char * pname = "Andy";

	static int sum = 0;

	char szName[5] = {'D','o','g','y'};

	cbyte * dvec = new cbyte[128];
	delete[] dvec;
}


