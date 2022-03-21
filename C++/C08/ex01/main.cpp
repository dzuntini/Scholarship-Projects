// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2022/03/17 12:31:12 by dzuntini          #+#    #+#             //
//   Updated: 2022/03/17 12:31:20 by dzuntini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Span.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main()
{
	Span sp(5);
	int n;

	srand(time(NULL));
	std::cout << "Let's add some numbers to span...\n" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		n = rand() % 100;
		std::cout << "Adding the number " << n << " to the span" << std::endl;
		sp.addNumber(n);
	}

	std::cout << "\n" << sp << std::endl;
	std::cout << "\nLet's try adding more that span can handle..." << std::endl;
	try
	{
		sp.addNumber(4);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " <<e.what() << std::endl;
	}


	std::cout << "\nLet's create a span of 42000\nAdding elements..." << std::endl;
	Span sp1(42000);

	for (int i = 0; i < 42000; i++)
	{
		if (i % 2)
			n = rand() % 10000;
		else
			n = (rand() % 100000) * (-1);
		sp1.addNumber(n);
	}
	std::cout << "\n" << sp1 << std::endl;


	std::cout << "\nLet's test adding elements with an iterator" << std::endl;
	std::vector<int>vect;
	Span sp2(10);

	for (int i = 0; i < 10; i++)
		vect.push_back(rand() % 100);

	sp2.addNumber(vect.begin(), vect.end());
	std::cout << sp2 << std::endl;

	return (0);
}
