#pragma once
#include<iostream>
using namespace std;
#include<vector>

class Bitset
{
public:
	Bitset(size_t value)
	{
		_a.resize((value >> 5) + 1, 0);
	}
	bool set(size_t num)
	{
		size_t index = num>>5;
		size_t pos = num % 32;
		if (_a[index] & (1 << (31 - pos)))
		{
			return false;
		}
		else
		{
			_a[index] |= (1 << (31 - pos));
			_size++;
			return true;
		}
		
	}
	bool Reset(size_t num)
	{
		size_t index = num >> 5;
		size_t pos = num % 32;
		if (Text(num))
		{
			_a[index] &= ~(1 << (31 - pos));
			_size--;
			return true;
		}
		else
		{
			return false;
		}
	}
	bool Text(size_t num)
	{
		size_t index = num >> 5;
		size_t pos = num % 32;
		return _a[index] & (1 << (31-pos));
	}
private:
	vector<int> _a;
	size_t _size;
};

void TextBitset()
{
	Bitset bt(50);
	bt.set(1);
	bt.set(8);
	bt.set(33);
}