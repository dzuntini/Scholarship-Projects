//
// Created by David Zuntini on 3/10/22.
//

#ifndef EX00_AANIMAL_HPP
#define EX00_AANIMAL_HPP

#include <iostream>

class AAnimal
{
public:
	virtual ~ AAnimal();
	virtual AAnimal &operator=(AAnimal *op) = 0;
	virtual void makeSound() const;
	std::string getType() const;
protected:
	std::string type;


};


#endif //EX00_AANIMAL_HPP
