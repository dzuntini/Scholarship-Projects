//
// Created by David Zuntini on 3/17/22.
//

#ifndef EX00_EASYFIND_HPP
#define EX00_EASYFIND_HPP
#include <algorithm>
template <typename T>
typename T::iterator easyfind(T &tab, int search)
{
	return (std::find(tab.begin(),tab.end(), search));
}



#endif //EX00_EASYFIND_HPP
