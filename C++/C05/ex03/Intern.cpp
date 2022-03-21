//
// Created by David Zuntini on 3/15/22.
//

#include "Intern.hpp"

Intern::Intern()
{
	uselss = 0;
}

Intern::Intern(Intern &cp)
{
	*this = cp;
}

Intern::~Intern()
{
}

Intern &Intern::operator=(const Intern &op)
{
	uselss = op.uselss;
	return(*this);
}

Form *Intern::makeForm(std::string form_name, std::string target)
{
	Form	*result;

	t_form	data[] =
			{
					{ "presidential pardon", new PresidentialPardonForm(target) },
					{ "robotomy request", new RobotomyRequestForm(target) },
					{ "shrubbery creation", new ShrubberyCreationForm(target) },
					{ "", NULL }
			};

	result = NULL;
	for (int i = 0; data[i].form != NULL; i++)
	{
		if (data[i].type == form_name)
			result = data[i].form;
		else
			delete data[i].form;
	}

	if (result == NULL)
		std::cout << "Intern could not find the form " << form_name << std::endl;
	else
		std::cout << "Intern creates " << form_name << std::endl;
	return result;
}
