//
// Created by David Zuntini on 3/10/22.
//

#include "Dog.hpp"

Dog::Dog()
{
	type = "Dog";
	std::cout << "Dog Default Constructor Called" << std::endl;
	b = new Brain();
}

Dog::Dog(const Dog &cp)
{
	*this = cp;
}

Dog::~Dog()
{
	std::cout << "Dog Destructor Called" << std::endl;
	delete b;
}

Dog &Dog::operator=(const Dog &op)
{
	std::cout << "Dog attributor Called" << std::endl;
	this->type = op.type;
	this->b = op.b;
	return(*this);
}


AAnimal &Dog::operator=(AAnimal *op)
{
	const Dog *atodog;

	atodog = dynamic_cast<const Dog*>(op);
	if (atodog)
	{
		this->type = op->getType();
		this->b =new Brain();
	}
	return (*this);
}

void Dog::makeSound() const
{
	std::cout << "Dog generic sound" << std::endl;
}

