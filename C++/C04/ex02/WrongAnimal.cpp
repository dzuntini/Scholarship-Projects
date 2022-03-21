//
// Created by David Zuntini on 3/10/22.
//

#include "WrongAnimal.hpp"
WrongAnimal::WrongAnimal()
{
	std::cout << "Default Constructor of WrongAnimal" << std::endl;
	this->type = "WrongAnimal";
}


WrongAnimal::WrongAnimal(const WrongAnimal& other)
{
	std::cout << "Copy-Constructor of WrongAnimal" << std::endl;
	*this = other;
}

WrongAnimal::~WrongAnimal()
{
	std::cout << "Destructor of WrongAnimal" << std::endl;
}

WrongAnimal	&WrongAnimal::operator=(const WrongAnimal& op)
{
	std::cout << "Animal attributor Called" << std::endl;
	this->type = op.type;
	return(*this);
}

void	WrongAnimal::makeSound() const
{
	std::cout << "* WrongAnimal Sound!!! *" << std::endl;
}

std::string WrongAnimal::getType() const
{
	return (this->type);
}
