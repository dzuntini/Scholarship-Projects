//
// Created by David Zuntini on 3/10/22.
//

#ifndef EX00_DOG_HPP
#define EX00_DOG_HPP

#include "AAnimal.hpp"
#include "Brain.hpp"

class Dog : public AAnimal
{
public:
	Dog();
	Dog( Dog const &cp);
	virtual ~Dog();
	Dog &operator=(const Dog &op);
	AAnimal &operator=(AAnimal *op);
	void makeSound() const;

private:
	Brain *b;
};


#endif //EX00_DOG_HPP
