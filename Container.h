#pragma once
#include <cmath>
#include <assert.h>
#include <cstdint>
#include <iostream>
using namespace std;

template<class T>
class Container
{
public:
	Container();
	Container(uint32_t size);
	Container(Container<T> const & other);
	T & operator[] (uint32_t ind) const;
	void push(T const & value);
	void pop();
	void reserve(uint32_t cap);
	void print(std::ostream & stream) const;

	uint32_t size() const
	{
		return sm_size;
	}
	bool empty() const
	{
		return sm_size == 0;
	}
	void clear();

private:
	uint32_t sm_size, sm_cap;
	uint8_t * buf;
};

template<class T>
Container<T>::Container(): 
	sm_size(0), sm_cap(0), buf(new uint8_t[sm_cap * sizeof(T)]){}

template<class T>
Container<T>::Container(uint32_t size): 
	sm_size(0), sm_cap(size), buf(new uint8_t[sm_cap * sizeof(T)]){}

template<class T>
Container<T>::Container(Container<T> const & other): 
	sm_size(other.sm_size), sm_cap(other.sm_cap), buf(new uint8_t[sm_cap * sizeof(T)])
{
	for (uint32_t i = 0; i < sm_size; i++) 
	{
		new(buf + i * sizeof(T)) T(other[i]);
	}
}

template<class T>
T & Container<T>::operator [] (uint32_t ind) const
{
	if (ind >= sm_size) throw exception("Invalid memory access.\n");
	return (T &)buf[ind * sizeof(T)];
}

template<class T>
void Container<T>::push(T const & value)
{
	if (sm_size == sm_cap)
	{
		reserve(sm_cap * 2 + 1);
	}
	new(buf + sm_size * sizeof(T)) T(value);
	sm_size++;
}

template<class T>
void Container<T>::pop()
{
	if (empty()) throw exception("Invalid memory access.\n");

	this->operator[](sm_size - 1).~T();
	sm_size--;
}

template<class T>
void Container<T>::reserve(uint32_t cap)
{
	if (sm_cap > cap) return;
	uint8_t * tmp = new uint8_t[cap * sizeof(T)];
	sm_cap = cap;
	if (sm_size != 0)
	{
		for (uint32_t i = 0; i < sm_size * sizeof(T); i++)
		{
			tmp[i] = buf[i];
		}
	}
	delete[] buf;
	buf = tmp;
}

template<class T>
void Container<T>::print(std::ostream & stream) const
{
	stream << "Size: " << size() << "  Empty: " << empty() << endl;
	stream << endl;
	uint32_t s = size();
	for (uint32_t i = 0; i < s; i++)
	{
		stream << *((T &)buf[i * sizeof(T)]) << endl;
	}
}

template<class T>
void Container<T>::clear()
{
	uint32_t s = size();
	for (uint32_t i = 0; i < s; i++)
	{
		pop();
	}
	sm_size = 0;
	sm_cap = 0;
	delete[] buf;
}