//
// Created by David Zuntini on 3/10/22.
//

#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
	Animal *tab[6];
	Animal a;
	for (int i = 0;i < 3;i++)
		tab[i] = new Cat();
	for (int i = 3;i < 6;i++)
		tab[i] = new Dog();
	for (int i = 0;i < 6;i++)
		tab[i]->makeSound();
	for (int i = 0;i < 6;i++)
		delete tab[i];
	a = new Animal();
	a.makeSound();
	return 0;
}
