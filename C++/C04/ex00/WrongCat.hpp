//
// Created by David Zuntini on 3/10/22.
//

#ifndef EX00_WRONGCAT_HPP
#define EX00_WRONGCAT_HPP

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal
{
public:
	WrongCat();
	WrongCat(WrongCat const &cp);
	virtual ~WrongCat();
	WrongCat &operator=(const WrongCat &op);
};


#endif //EX00_WRONGCAT_HPP
