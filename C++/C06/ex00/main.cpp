//
// Created by David Zuntini on 3/15/22.
//

#include "Scalaire.hpp"


/*static_cast performs implicit conversions, the reverses of implicit standard conversions, and (possibly unsafe) base to derived conversions.*/
int main(int ac , char **av)
{

	if (ac == 2)
	{
		Scalaire *a = new Scalaire(av[1]);
		try
		{
			a->print();
		}
		catch (std::exception &e)
		{
			std::cout << "Exception: " << e.what() << std::endl;
		}
		delete a;
	}
	else
		std::cout << "Wrong numbers of args" << std::endl;
}
