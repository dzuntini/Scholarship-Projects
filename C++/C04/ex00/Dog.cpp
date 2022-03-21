//
// Created by David Zuntini on 3/10/22.
//

#include "Dog.hpp"

Dog::Dog()
{
	type = "Dog";
	std::cout << "Dog Default Constructor Called" << std::endl;
}

Dog::Dog(const Dog &cp)
{
	*this = cp;
}

Dog::~Dog()
{
	std::cout << "Dog Destructor Called" << std::endl;
}

Dog &Dog::operator=(const Dog &op)
{
	std::cout << "Dog attributor Called" << std::endl;
	this->type = op.type;
	return(*this);
}

void Dog::makeSound() const
{
	std::cout << "Dog generic sound" << std::endl;
}
