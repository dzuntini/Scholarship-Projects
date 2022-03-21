//
// Created by David Zuntini on 3/10/22.
//

#include "WrongCat.hpp"

WrongCat::WrongCat()
{
	type = "WrongCat";
	std::cout << "WrongCat Default Constructor Called" << std::endl;
}


WrongCat::WrongCat(const WrongCat &cp)
{
	std::cout << "Copy-Constructor of WrongCat" << std::endl;
	*this = cp;
}


WrongCat::~WrongCat()
{
	std::cout << "WrongCat has been destroyed" << std::endl;
}

WrongCat &WrongCat::operator=(const WrongCat &op)
{
	std::cout << "WrongCat attributor Called" << std::endl;
	this->type = op.type;
	return(*this);
}

