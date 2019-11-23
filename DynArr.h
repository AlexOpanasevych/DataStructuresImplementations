// Single-header implementation of dynamic array container

#pragma once

#include <iostream>

template <typename T> class DynArr {
	T * data;
	size_t _size;
	size_t _capacity;
public:

	bool empty() {
		return _size == 0;
	}



	unsigned int size() {
		return _size;
	}

	void reserve(int reserve_size) {
		if (_size > reserve_size) {
			return;
		}
		else {
			T * newData = new T[reserve_size];
			if (_size > 0) {
				for (int i = 0; i < _size; i++) {
					newData[i] = data[i];
				}
			}
			data = newData;
		}
		_capacity = reserve_size;
	}

	void assign(const T & elem) {
		T * newData = new T[_size + 1];
		if (_size > 0)
		{
			for (size_t i = 0; i < _size; i++)
				newData[i] = this->data[i];
			delete[] this->data;
		}
		newData[_size] = elem;
		data = newData;
		_size++;
	}

	void remove_last() {
		(reinterpret_cast<T*>(data)[_size - 1]).~T();
		_size--;
	}

	void remove(int pos) {
		for (size_t i = pos + 1; i < _size; i++)
		{
			data[i - 1] = data[i];
		}
		remove_last();
	}

	~DynArr();

	DynArr();

	T & at(int i)
	{
		try {
			if (i < 0 || i > _size - 1)
				throw std::exception();
			return data[i];
		}
		catch (std::exception & e) {
			std::cerr << e.what() << std::endl;
			exit(1);
		}
	}

	DynArr<T> & operator=(const DynArr <T> & rhs) {
		delete[] data;
		_size = rhs._size;
		_capacity = rhs._capacity;
		data = new T[_capacity];
		for (int i = 0; i < _size; i++)
		{
			data[i] = rhs.data[i];
		}
		return *this;
	}

	T & operator[](int i) {
		return at(i);
	}

	explicit DynArr(const int reserve_size) : _size(reserve_size), data(new T[reserve_size]), _capacity(2 * reserve_size) {}

	DynArr(const DynArr<T> & rhs);

	friend std::ostream & operator<<(std::ostream & stream, const DynArr<T> & to_print) {
		try {
			stream << "[";
			for (int i = 0; i < to_print._size; ++i) {
				stream << to_print.data[i];
				if (i != to_print._size - 1)
					stream << ", ";
			}
			stream << ']';
		}
		catch (const std::exception & e) {
			std::cerr << e.what() << std::endl;
		}
		return stream;
	}

};

template <typename T> DynArr<T>::~DynArr()
{
	delete[] data;
}

template <typename T> DynArr<T>::DynArr() : _size(0), _capacity(10000) {
	data = new T[_size + 1];
}

template <typename T> DynArr<T>::DynArr(const DynArr<T> & rhs) :
	_size(rhs._size),
	_capacity(rhs._capacity),
	data(new T[rhs._size])
{
	for (unsigned int i = 0; i < _size; i++)
	{
		new (data + sizeof(T) * i) T(rhs.data[i]);
	}
}
