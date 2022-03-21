// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2022/02/14 13:22:05 by dzuntini          #+#    #+#             //
//   Updated: 2022/02/14 13:22:06 by dzuntini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>

int main()
{
	std::string s;
	std::string *stringPTR;
	std::string &stringREF = s;

	s = "HI THIS IS BRAIN";
	stringPTR = &s;
	std::cout << "PTR add = " << stringPTR << '\n';
	std::cout << "REF add = " << &stringREF << '\n';
	std::cout << "PTR val = " << *stringPTR << '\n';
	std::cout << "REF val = " << stringREF << '\n';

}