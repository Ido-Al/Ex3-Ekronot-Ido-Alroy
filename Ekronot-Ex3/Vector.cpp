#include "Vector.h"
Vector::Vector(int n)
{
	if (n < 2)
	{
		n = 2;
	}
	_elements = new int[n];
	_size = 0;
	_capacity = n;
	_resizeFactor = n;
}
Vector::~Vector()
{
	delete[] _elements;
}
int Vector::size() const
{
	return _size;
}
int Vector::capacity() const
{
	return _capacity;
}
int Vector::resizeFactor() const
{
	return _resizeFactor;
}
bool Vector::empty() const
{
	return _size == 0;
}
//adds element at the end of the vector
void Vector::push_back(const int& val)
{
	if (_size >= _capacity)
	{
		_capacity = _capacity + _resizeFactor;
		int* newElements = new int[_capacity];
		for (int i = 0; i < _size; i++) 
		{
			newElements[i] = _elements[i];
		}
		delete[] _elements;
		_elements = newElements;
	}
	_elements[_size] = val;
	_size++;
}
//removes and returns the last element of the vector
int Vector::pop_back()
{
	if (_size == 0)
	{
		return -9999; // error
	}
	_size--;
	return _elements[_size]; // size starts at one so size - 1 is the last element 
}
//change the capacity
void Vector::reserve(const int n)
{
	if (n < _capacity)
	{
		return;
	}
	int remainder = n % _resizeFactor;
	int newCapacity = n + (_resizeFactor - remainder) * (remainder != 0); // round n to the nearest multiple of _resizeFactor
	int* newElements = new int[newCapacity];
	for (int i = 0; i < _size; i++) {
		newElements[i] = _elements[i];
	}
	delete[] _elements;
	_elements = newElements;
	_capacity = newCapacity;
}
//change _size to n, unless n is greater than the vector's capacity
void Vector::resize(const int n)
{
	if (n > _capacity || n < 0)
	{
		return;
	}
	resize(n, 0);

}
//assigns val to all elemnts
void Vector::assign(const int val)
{
	for (int i = 0; i < _size; i++)
	{
		_elements[i] = val;
	}
}
//if new elements added their value is val
void Vector::resize(const int n, const int& val)
{
	if (n > _size)
	{
		for (int i = _size; i < n; i++)
		{
			_elements[i] = val;
		}
	}
	_size = n;
}