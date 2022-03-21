//
// Created by David Zuntini on 3/12/22.
//

#ifndef EX01_BRAIN_HPP
#define EX01_BRAIN_HPP

#include "Animal.hpp"

class Brain
{
public:
	Brain();
	Brain( Brain const &cp);
	virtual ~Brain();
	Brain &operator=(Brain*op);
private:
	std::string ideas[100];
	int size;
};


#endif //EX01_BRAIN_HPP
