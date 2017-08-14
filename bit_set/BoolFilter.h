#pragma once

#include"bite_set.h"
#include"Hash.h"
#include<string>

template<class T>
struct __HashFunk1
{
	size_t operator()(const T& key)
	{
		return BKDRHash<T>(key.c_str());
	}
};

template<class T>
struct __HashFunk2
{
	size_t operator()(const T& key)
	{
		return SDBMHash<T>(key.c_str());
	}
}; 

template<class T>
struct __HashFunk3
{
	size_t operator()(const T& key)
	{
		return RSHash<T>(key.c_str());
	}
};

template<class T>
struct __HashFunk4
{
	size_t operator()(const T& key)
	{
		return APHash<T>(key.c_str());
	}
};

template<class T>
struct __HashFunk5
{
	size_t operator()(const T& key)
	{
		return JSHash<T>(key.c_str());
	}
};


template<class K = string,
class HashFunk1 = __HashFunk1<K>,
class HashFunk2 = __HashFunk2<K>,
class HashFunk3 = __HashFunk3<K>,
class HashFunk4 = __HashFunk4<K>,
class HashFunk5 = __HashFunk5<K>>

class BoolFilter
{
public:
	BoolFilter(size_t n)
		:_a(n * 10)
		, _range(n * 10)
	{}

	void set(const K& key)
	{
		_a.set(HashFunk1()(key) % _range);
		_a.set(HashFunk2()(key) % _range);
		_a.set(HashFunk3()(key) % _range);
		_a.set(HashFunk4()(key) % _range);
		_a.set(HashFunk5()(key) % _range);
	}

	bool Text(const K& key)
	{
		if (!_a.Text(HashFunk1()(key)% _range))
			return false;
		if (!_a.Text(HashFunk2()(key) % _range))
			return false;
		if (!_a.Text(HashFunk3()(key) % _range))
			return false;
		if (!_a.Text(HashFunk4()(key) % _range))
			return false;
		if (!_a.Text(HashFunk5()(key) % _range))
			return false;
		return true;
	}
private:
	Bitset _a;
	size_t _range;
};

void TextBoolFilter()
{
	size_t i = 5;
	string s1 = "sort";
	string s2 = "last one";
	string s3 = "first one";
	string s4 = "https:\\www.hao123.com";

	BoolFilter<> b(i);
	while (i > 0)
	{
		b.set(s1);
		b.set(s2);
		b.set(s3);
		b.set(s4);
		i--;
	}
	cout << b.Text(s1)<<endl;
	cout << b.Text(s2) << endl;
	cout << b.Text(s3) << endl;
	cout << b.Text(s4) << endl;
	cout << b.Text("1111dada") << endl;


}