//
// Created by David Zuntini on 3/16/22.
//

#ifndef EX01_ITER_HPP
#define EX01_ITER_HPP

template<typename T>
void iter(T *tab, int len, void (*func)(T&))
{
	for (int i = 0; i < len; i++)
		func(tab[i]);
}

#endif //EX01_ITER_HPP
