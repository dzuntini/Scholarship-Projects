//
// Created by David Zuntini on 3/15/22.
//

#ifndef EX03_INTERN_HPP
#define EX03_INTERN_HPP
#include "Form.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include <iostream>

class Intern
{
private:
	typedef struct	s_form
	{
		std::string	type;
		Form		*form;
	}				t_form;
	int uselss;
public:
	Intern();
	Intern(Intern &cp);
	virtual ~Intern();
	Intern &operator=(const Intern &op);
	Form *makeForm(std::string form_name, std::string target_name);
};


#endif //EX03_INTERN_HPP
