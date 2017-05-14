#pragma once

#include <string>
#include <cctype>

namespace helper
{
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

	int getTailNumt(std::string str)
	{
		std::string sub = "";
		for (int i=str.size()-1; i>=0; i--)
		{
			char c = str.at(i);
			if (isdigit(c))
				sub = c + sub;
		}
		
		return atoi(sub.c_str());
	}

	std::string cutTailNumt(std::string str)
	{

		for (int i = str.size() - 1; i >= 0; i--)
		{
			char c = str.at(i);
			if (!isdigit(c))
			{
				return str.substr(0, i + 1);
				break;
			}
		}

		return "";
	}
};
