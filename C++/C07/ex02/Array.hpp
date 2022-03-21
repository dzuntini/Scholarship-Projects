//
// Created by David Zuntini on 3/16/22.
//

#ifndef EX02_ARRAY_HPP
#define EX02_ARRAY_HPP
#include <iostream>

template <typename T>
class Array
{
private:
	T	*data;
	int	size;
public:

	Array();
	Array(unsigned int n);
	Array(const Array& copy);
	~Array();

	T&		operator[](int idx) const;
	Array&	operator=(const Array& other);
	int		getsize() const;
};

template <typename T>
Array<T>::Array() : data(NULL), size(0) {}

template <typename T>
Array<T>::Array(unsigned int n) : data(new T[n]), size(n) {}

template <typename T>
Array<T>::Array(const Array& copy) : size(copy.size)
{
	for (int i = 0; i < copy.size; i++)
		this->data[i] = copy.data[i];
}

template <typename T>
Array<T>::~Array()
{
	delete[] this->data;
}

template <typename T>
Array<T>&	Array<T>::operator=(const Array& other)
{
	if (this == &other)
		return (*this);
	if (this->size > 0)
		delete[] this->data;

	this->size = other.size;
	this->data = new T[size];
	for (int i = 0; i < size; i++)
		this->data[i] = other.data[i];
	return (*this);
}

template <typename T>
T&			Array<T>::operator[](int idx) const
{
	if (idx < 0 || idx >= size)
		throw std::overflow_error("Index out of bounds");
	return (this->data[idx]);
}

template <typename T>
int			Array<T>::getsize() const
{
	return (this->size);
}

template <typename T>
std::ostream&	operator<<(std::ostream& out, const Array<T>& array)
{
	out << "Array = { ";
	for (int i = 0; i < array.getsize(); i++)
	{
		out << array[i];
		if (i != array.getsize() - 1)
			out << ", ";
	}
	out << " }";
	return (out);
}
#endif //EX02_ARRAY_HPP
