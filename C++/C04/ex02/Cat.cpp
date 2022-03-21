//
// Created by David Zuntini on 3/10/22.
//

#include "Cat.hpp"

Cat::Cat()
{
	std::cout << "Cat Default Constructor Called" << std::endl;
	type = "Cat";
	b = new Brain();
}

Cat::Cat(const Cat &cp)
{
	*this = cp;
}

Cat::~Cat()
{
	std::cout << "Cat Destructor Called" << std::endl;
	delete b;
}

Cat &Cat::operator=(const Cat &op)
{
	std::cout << "Cat attributor Called" << std::endl;
	this->type = op.type;
	this->b = op.b;
	return(*this);
}


AAnimal &Cat::operator=(AAnimal *op)
{
	const Cat *atodog;

	atodog = dynamic_cast<const Cat*>(op);
	if (atodog)
	{
		this->type = op->getType();
		this->b =new Brain();
	}
	return (*this);
}

void Cat::makeSound() const
{
	std::cout << "Cat generic sound" << std::endl;
}
