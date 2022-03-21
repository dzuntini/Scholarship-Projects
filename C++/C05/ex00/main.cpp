//
// Created by David Zuntini on 3/12/22.
//

#include "Bureaucrat.hpp"

int main()
{
	Bureaucrat	Odin("Odin", 1);
	Bureaucrat	Loki("Loki", 150);

	std::cout << "Just created two bureaucrat gods!" << std::endl;
	std::cout << Odin << std::endl;
	std::cout << Loki << std::endl;

	std::cout << "\nLet's try creating Thor with grade 0" << std::endl;
	/* GradeTooHighException */
	try
	{
		Bureaucrat Thor("Thor", 0);
	}
	catch (std::exception& e)
	{
		std::cout << "Cannot create Thor!" << std::endl;
		std::cout << "Exception: " << e.what() << std::endl;
	}
	std::cout << "\nLet's try creating John with grade 151" << std::endl;
	/* GradeTooLowException */
	try
	{
		Bureaucrat John("Thor", 151);
	}
	catch (std::exception& e)
	{
		std::cout << "Cannot create John!" << std::endl;
		std::cout << "Exception: " << e.what() << std::endl;
	}
	std::cout << "\nLet's try promoting Odin!" << std::endl;
	/* Increment throwing exception */
	try
	{
		Odin.incrementGrade();
	}
	catch (std::exception& e)
	{
		std::cout << "Cannot increment the grade of Odin!" << std::endl;
		std::cout << "Exception: " << e.what() << std::endl;
	}
	std::cout << "\nLet's try demoting Loki!" << std::endl;
	/* Decrement throwing exception */
	try
	{
		Loki.decrementGrade();
	}
	catch (std::exception& e)
	{
		std::cout << "Cannot decrement the grade of Loki!" << std::endl;
		std::cout << "Exception: " << e.what() << std::endl;
	}
	try
	{
		std::cout << "\n"<< Loki;
		std::cout << Odin;
		Loki.incrementGrade();
		Odin.decrementGrade();
		std::cout << Loki;
		std::cout << Odin;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}
}
