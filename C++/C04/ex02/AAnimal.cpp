//
// Created by David Zuntini on 3/10/22.
//

#include "AAnimal.hpp"

AAnimal::~ AAnimal()
{
	std::cout << "AAnimal Destructor Called" << std::endl;
}

void	AAnimal::makeSound() const
{
	std::cout << "I'm animal" << std::endl;
}

std::string	AAnimal::getType() const
{
	return (this->type);
}
