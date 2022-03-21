//
// Created by David Zuntini on 3/10/22.
//

#include "Animal.hpp"

Animal::Animal()
{
	type = "Animal";
	std::cout << "Animal Default Constructor Called" << std::endl;
}

Animal::Animal(const Animal &cp)
{
	std::cout << "Animal Copy Constructor Called" << std::endl;
	*this = cp;
}

Animal::~Animal()
{
	std::cout << "Animal Destructor Called" << std::endl;
}

Animal &Animal::operator=(Animal*op)
{
	std::cout << "Animal attributor Called" << std::endl;
	this->type = op->type;
	return(*this);
}

void	Animal::makeSound() const
{
	std::cout << "I'm animal" << std::endl;
}

std::string Animal::getType() const
{
	return (this->type);
}
