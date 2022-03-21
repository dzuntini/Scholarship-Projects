//
// Created by David Zuntini on 3/16/22.
//

#include "Array.hpp"
#include <iostream>
#include <cstdlib>

int	main()
{
	Array<int>			intArray;
	Array<int>			copy(5);
	Array<std::string>	strArray(5);

	for (int i = 0; i < 5; i++)
		copy[i] = rand() % 100;

	std::cout << "intArray size: " << intArray.getsize() << std::endl;
	std::cout << "strArray size: " << strArray.getsize() << std::endl;
	std::cout << "copy size: " << intArray.getsize() << std::endl;

	std::cout << "\nLet's assign copy to intArray..." << std::endl;
	intArray = copy;
	std::cout << intArray << std::endl;

	std::cout << "\nLet's write the strArray with strings..." << std::endl;
	strArray[0] = "Lufi";
	strArray[1] = "Ace";
	strArray[2] = "Sabo";
	strArray[3] = "Dragon";
	strArray[4] = "Garp";
	std::cout << strArray << std::endl;

	std::cout << "\nLet's try getting elems out of intArray size" <<std::endl;
	try
	{
		std::cout << intArray[59] << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "59: " << e.what() << std::endl;
	}

	try
	{
		std::cout << intArray[-3] << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "-3: " << e.what() << std::endl;
	}
	return (0);
}
