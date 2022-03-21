//
// Created by David Zuntini on 3/17/22.
//

#include "Span.hpp"
Span::Span() : N(0)
{
	this->storage.reserve(0);
}

Span::Span(unsigned int N) : N(N)
{
	this->storage.reserve(N);
}

Span::Span(const Span& other)
{
	*this = other;
}

Span::~Span() {}

Span&	Span::operator=(const Span& other)
{
	this->N = other.N;
	this->storage = other.storage;

	return (*this);
}

int		Span::size() const
{
	return (this->storage.size());
}

int		Span::capacity() const
{
	return (this->N);
}

void	Span::addNumber(int n)
{
	if (this->storage.size() == N)
		throw std::overflow_error("Span has no more free spaces");
	this->storage.push_back(n);
}

int		Span::shortestSpan() const
{
	std::vector<int>	tmp;

	tmp = storage;
	if (storage.size() < 2)
		throw std::logic_error("Not enough numbers stored to provide a span");
	std::sort(tmp.begin(), tmp.end());
	return (tmp[1] - tmp[0]);
}

int		Span::longestSpan() const
{
	std::vector<int>	tmp;

	tmp = storage;
	if (storage.size() < 2)
		throw std::logic_error("Not enough numbers stored to provide a span");
	std::sort(tmp.begin(), tmp.end());
	return (tmp.back() - tmp.front());
}

std::ostream&	operator<<(std::ostream& out, const Span& instance)
{
	std::cout << "Span of max size " << instance.capacity();
	std::cout << " contains " << instance.size() << " numbers,";
	std::cout << " shortest span is " << instance.shortestSpan();
	std::cout << " and longest is " << instance.longestSpan();
	return (out);
}