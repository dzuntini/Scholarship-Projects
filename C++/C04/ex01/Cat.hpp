//
// Created by David Zuntini on 3/10/22.
//

#ifndef EX00_CAT_HPP
#define EX00_CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
public:
	Cat();
	Cat(Cat const &cp);
	virtual ~Cat();
	Cat &operator=(const Cat &op);
	void makeSound() const;

private:
	Brain *b;
};


#endif //EX00_CAT_HPP
