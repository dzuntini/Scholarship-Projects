//
// Created by David Zuntini on 3/17/22.
//

#ifndef EX01_SPAN_HPP
#define EX01_SPAN_HPP

#include <iostream>
#include <vector>

class Span
{
private:
	std::vector<int>		storage;
	unsigned int			N;
public:
	Span();
	Span(unsigned int N);
	Span(const Span& other);
	~Span();

	Span&	operator=(const Span& other);
	int		size() const;
	int		capacity() const;
	void	addNumber(int n);
	int		shortestSpan() const;
	int		longestSpan() const;

	template <typename It>
	void	addNumber(It begin, It end)
	{
		while (begin != end)
		{
			this->addNumber(*begin);
			begin++;
		}
	}
};

std::ostream&	operator<<(std::ostream& out, const Span& instance);

#endif //EX01_SPAN_HPP
