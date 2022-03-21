//
// Created by David Zuntini on 3/12/22.
//

#include "Brain.hpp"

Brain::Brain()
{
	std::cout << "Brain default constructor" << std::endl;
	size = 0;
}

Brain::Brain(const Brain &cp)
{
	std::cout << "Brain copy constructor" << std::endl;
	*this = cp;
}

Brain::~Brain()
{
	std::cout << "Brain destructor" << std::endl;
}

Brain &Brain::operator=(Brain *op)
{
	std::cout << "Brain operator" << std::endl;
	for (int i = 0; i < 100; i++)
		this->ideas[i] = op->ideas[i];
	this->size = op->size;
	return (*this);
}
