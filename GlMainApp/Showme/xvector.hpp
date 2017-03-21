#pragma once

#include<vector>
#include <string>
#include <sstream>

template <class T>
class GVector
{
public:

	GVector() {}
	GVector(int i) { vec.resize(i); }
	GVector(T *p, size_t n)
	{
		for (size_t i = 0; i < n; i++)
			vec.push_back(p[i]);
	}

	std::wstring toString()
	{
		std::wstringstream ws;
		for (T v : vec)
			ws << v << L"\t";

		return ws.str();
	}

	size_t size() { return vec.size(); }

	GVector(GVector & other)
	{
		vec.resize(other.size());
		for(size_t i = 0; i< other.size(); i++)
			vec[i] = other.vec[i];
	}
	GVector operator = (GVector & other)
	{
		vec.resize(other.size());
		for (size_t i = 0; i< other.size(); i++)
			vec[i] = other.vec[i];
	}

	GVector operator + ( GVector & other)
	{
		GVector ret = GVector();
		ret.vec.resize(other.size());
		if (other.size() != this->size())
		{
			throw("size not equal");
		}

		for (size_t i = 0; i < size(); i++)
		{
			ret.vec[i] = vec[i] + other.vec[i];
		}

		return ret;
	}

	T operator [](int i) { return vec[i]; }
	
private:
	std::vector<T> vec;
};