//
// Created by David Zuntini on 3/17/22.
//

#ifndef EX02_MUTANTSTACK_HPP
#define EX02_MUTANTSTACK_HPP

#include <stack>

template <typename T>
class MutantStack : public std::stack<T>
		{
		public:
			typedef typename std::stack<T>::container_type::iterator iterationer;
			iterationer	begin() { return this->c.begin(); };
			iterationer	end() { return this->c.end(); };	//need c as a base object for container type so stack dont call itself ??Weird recursive issue
		};


#endif //EX02_MUTANTSTACK_HPP
