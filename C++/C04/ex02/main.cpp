//
// Created by David Zuntini on 3/10/22.
//

#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
	AAnimal *tab[6];

	for (int i = 0;i < 3;i++)
		tab[i] = new Cat();
	for (int i = 3;i < 6;i++)
		tab[i] = new Dog();
	for (int i = 0;i < 6;i++)
		tab[i]->makeSound();
	for (int i = 0;i < 6;i++)
		delete tab[i];
	//AAnimal a = new AAnimal();
	//AAnimal b;
	//a.makeSound();
	return 0;
}
