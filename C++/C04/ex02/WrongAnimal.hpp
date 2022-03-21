//
// Created by David Zuntini on 3/10/22.
//

#ifndef EX00_WRONGANIMAL_HPP
#define EX00_WRONGANIMAL_HPP

#include "AAnimal.hpp"

class WrongAnimal
{
public:
	WrongAnimal();
	WrongAnimal(WrongAnimal const &cp);
	virtual ~WrongAnimal();
	WrongAnimal &operator=(const WrongAnimal &op);
	virtual void makeSound() const;
	std::string getType() const;
protected:
	std::string type;


};
#endif //EX00_WRONGANIMAL_HPP
