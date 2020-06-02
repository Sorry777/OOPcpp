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
	void reserve(uint32_t capacity);
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
	uint32_t sm_size, sm_capacity;
	uint8_t * m_buf;
};

template<class T>
Container<T>::Container(): 
	sm_size(0), sm_capacity(0), m_buf(nullptr){}

template<class T>
Container<T>::Container(uint32_t size): 
	sm_size(0), sm_capacity(size), m_buf(new uint8_t[sm_capacity * sizeof(T)]){}

template<class T>
Container<T>::Container(Container<T> const & other): 
	sm_size(other.sm_size), sm_capacity(other.sm_capacity), m_buf(new uint8_t[sm_capacity * sizeof(T)])
{
	for (uint32_t i = 0; i < sm_size; i++) 
	{
		new(m_buf + i * sizeof(T)) T(other[i]);
	}
}

template<class T>
T & Container<T>::operator [] (uint32_t ind) const
{
	if (ind >= sm_size) throw("Invalid memory access.\n");
	return (T &)m_buf[ind * sizeof(T)];
}

template<class T>
void Container<T>::push(T const & value)
{
	if (sm_size == sm_capacity)
	{
		reserve(sm_capacity * 2 + 1);
	}
	new(m_buf + sm_size * sizeof(T)) T(value);
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
void Container<T>::reserve(uint32_t capacity)
{
	if (sm_capacity > capacity) return;
	uint8_t * tmp = new uint8_t[capacity * sizeof(T)];
	sm_capacity = capacity;
	if (sm_size != 0)
	{
		for (uint32_t i = 0; i < sm_size * sizeof(T); i++)
		{
			tmp[i] = m_buf[i];
		}
	}
	delete[] m_buf;
	m_buf = tmp;
}

template<class T>
void Container<T>::print(std::ostream & stream) const
{
	stream << "Size: " << size() << "  Empty: " << empty() << endl;
	stream << endl;
	uint32_t s = size();
	for (uint32_t i = 0; i < s; i++)
	{
		stream << *((T &)m_buf[i * sizeof(T)]) << endl;
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
	sm_capacity = 0;
	delete[] m_buf;
}