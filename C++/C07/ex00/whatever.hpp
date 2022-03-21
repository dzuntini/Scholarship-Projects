//
// Created by David Zuntini on 3/16/22.
//

#ifndef EX00_WHATEVER_HPP
#define EX00_WHATEVER_HPP

template<typename T>
void		swap(T& a, T& b)
{
	T	tmp;

	tmp = a;
	a = b;
	b = tmp;
}

template<typename T>
const T&	min(T& a, T& b)
{
	return (a < b ? a : b);
}

template<typename T>
const T&	max(T& a, T& b)
{
	return (a > b ? a : b);
}

#endif //EX00_WHATEVER_HPP
