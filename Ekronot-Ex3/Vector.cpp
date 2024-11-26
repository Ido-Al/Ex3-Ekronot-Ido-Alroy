#include "Vector.h"
#include <string>
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
		std::cout << "cant pop an empty vector\n";
		return -9999; // error
	}
	_size--;
	return _elements[_size]; // size starts at one so size - 1 is the last element 
}
//change the capacity
void Vector::reserve(const int n)
{
	if (n <= _capacity)
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
	if (n > _capacity || n < 0)
	{
		reserve(n);
	}
	if (n > _size)
	{
		for (int i = _size; i < n; i++)
		{
			_elements[i] = val;
		}
	}
	_size = n;
}
Vector::Vector(const Vector& other)
{
	_size = other._size;
	_capacity = other._capacity;
	_resizeFactor = other._resizeFactor;
	_elements = new int[_capacity];
	for (int i = 0; i < _size; i++) 
	{
		_elements[i] = other._elements[i];
	}
}


Vector& Vector::operator=(const Vector& other)
{
	if (this == &other)
	{
		return *this;
	}
	_size = other._size;
	_capacity = other._capacity;
	_resizeFactor = other._resizeFactor;
	if (_elements != nullptr)
	{
		delete[] _elements;
	}
	_elements = new int[_capacity];
	for (int i = 0; i < _size; i++)
	{
		_elements[i] = other._elements[i];
	}
	return *this;

}
int& Vector::operator[](int n) const
{
	if (n > _size - 1 || n < 0) // size - 1 is the last element
	{
		std::cout << "Cant acess element not in range\n";
		return _elements[0];
	}
	return _elements[n];

}
// adds the content of the other vector to this vector
Vector& Vector::operator+=(const Vector& other)
{
	*this = *this + other;
	return *this;
}
// substracts the content of the other vector from this vector
Vector& Vector::operator-=(const Vector& other)
{
	*this = *this - other;
	return *this;
}
// returns a vector that contains the result of adding the other vector to this vector
Vector Vector:: operator+(const Vector& other) const
{
	Vector v3(_capacity > other._capacity ? _capacity : other._capacity);
	v3._size = (_size > other._size) ? _size : other._size;
	for (int i = 0; i < v3._capacity; i++)
	{
		int thisElement = (i < _size) ? _elements[i] : 0; // if out of bounds add 0
		int otherElement = (i < other._size) ? other._elements[i] : 0;
		v3._elements[i] = thisElement + otherElement;
	}
	return v3;
}
// returns a vector that contains the result of substratcting the other vector from this vector
Vector Vector::operator-(const Vector& other) const
{
	Vector v3(_capacity > other._capacity ? _capacity : other._capacity);
	v3._size = (_size > other._size) ? _size : other._size;
	for (int i = 0; i < v3._capacity; i++)
	{
		int thisElement = (i < _size) ? _elements[i] : 0; // if out of bounds add 0
		int otherElement = (i < other._size) ? other._elements[i] : 0;
		v3._elements[i] = thisElement - otherElement;
	}
	return v3;
}
// stream insertion - insert a vector stream to a given stream
std::ostream& operator<<(std::ostream& os, const Vector& v)
{
	/*Vector Info : \nCapacity is{ capacity }\nSize is{ size } data is{ val1, val2, val3,...,valn }\n*/
	std::string info = "";
	info += "Vector info:\n";
	info += "Capacity is " + std::to_string(v._capacity) + "\n";
	info += "Size is " + std::to_string(v._size) + "\n";
	info += "{";
	for (int i = 0; i < v._size - 1; i++)
	{
		info += std::to_string(v._elements[i]) + ",";
		
	}
	info += std::to_string(v._elements[v._size - 1]) + "}\n";
	os << info;
	return os;
}