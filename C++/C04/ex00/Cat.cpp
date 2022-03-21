//
// Created by David Zuntini on 3/10/22.
//

#include "Cat.hpp"

Cat::Cat()
{
	type = "Cat";
	std::cout << "Cat Default Constructor Called" << std::endl;
}

Cat::Cat(const Cat &cp)
{
	*this = cp;
}

Cat::~Cat()
{
	std::cout << "Cat Destructor Called" << std::endl;
}

Cat &Cat::operator=(const Cat &op)
{
	std::cout << "Cat attributor Called" << std::endl;
	this->type = op.type;
	return(*this);
}

void Cat::makeSound() const
{
	std::cout << "Cat generic sound" << std::endl;
}
