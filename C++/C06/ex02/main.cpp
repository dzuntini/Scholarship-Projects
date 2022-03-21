//
// Created by David Zuntini on 3/16/22.
//
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base	*generate(void)
{
	int	random;

	random = rand() % 3;
	if (random == 0)
		return (new A);
	if (random == 1)
		return (new B);
	if (random == 2)
		return (new C);
	else
		return (NULL);
}

void	identify(Base *p)
{
	if (dynamic_cast<A* >(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B* >(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C* >(p))
		std::cout << "C" << std::endl;
}

void	identify(Base &p)
{

	try
	{
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
	}
	catch(std::exception& e) {}
	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
	}
	catch(std::exception& e) {}
	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
	}
	catch(std::exception& e)
	{
		//Put stuff here to get flooded
		//std::cout << "C'est pas un C"
	}
}

/*dynamic_cast casts up and down class hierarchies only, always checking that the conversion requested is valid.*/
int	main()
{
	Base	*base;

	srand(time(NULL));
	std::cout << "Identifying with pointers\n" << std::endl;

	base = generate();
	identify(base);
	delete base;

	base = generate();
	identify(base);
	delete base;

	base = generate();
	identify(base);
	delete base;

	base = generate();
	identify(base);
	delete base;

	base = generate();
	identify(base);
	delete base;

	std::cout << "\nIdentifying with references\n" << std::endl;

	base = generate();
	identify(*base);
	delete base;

	base = generate();
	identify(*base);
	delete base;

	base = generate();
	identify(*base);
	delete base;

	base = generate();
	identify(*base);
	delete base;

	base = generate();
	identify(base);
	delete base;
}
