//
// Created by David Zuntini on 3/10/22.
//

#ifndef EX00_ANIMAL_HPP
#define EX00_ANIMAL_HPP

#include <iostream>

class Animal
{
public:
	Animal();
	Animal( Animal const &cp);
	virtual ~Animal();
	Animal &operator=(const Animal &op);
	virtual void makeSound() const;
	std::string getType() const;
protected:
	std::string type;


};


#endif //EX00_ANIMAL_HPP
