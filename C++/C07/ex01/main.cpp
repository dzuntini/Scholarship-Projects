//
// Created by David Zuntini on 3/16/22.
//

#include "iter.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

template<typename T>
void	display(T& elem)
{
	std::cout << "Variable's value is: " << elem << std::endl;
}

void	setRandomValue(int& number)
{
	number = rand() % 100;
}

void	setRandomValue(char& number)
{
	number = rand() % 50 + ' ';
}

int	main()
{
	int	intArray[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	char chararray[10] = "abcdefghi";

	srand(time(nullptr));

	std::cout << "Displaying int Array\n" << std::endl;
	iter<int>(intArray, 10, &display);

	std::cout << "\nSetting each value to random integer" << std::endl;
	iter<int>(intArray, 10, &setRandomValue);

	std::cout << "\nDisplaying int Array with random values\n" << std::endl;
	::iter<int>(intArray, 10, &display);

	std::cout << "\nDisplaying char Array\n" << std::endl;
	iter<char>(chararray, 10, &display);

	std::cout << "\nSetting each value to random char" << std::endl;
	iter<char>(chararray, 10, &setRandomValue);

	std::cout << "\nDisplaying char Array with random values\n" << std::endl;
	::iter<char>(chararray, 10, &display);

	return (0);
}
