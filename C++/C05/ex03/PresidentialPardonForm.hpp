//
// Created by David Zuntini on 3/15/22.
//

#ifndef EX02_PRESIDENTIALPARDONFORM_HPP
#define EX02_PRESIDENTIALPARDONFORM_HPP

#include <iostream>
#include "Form.hpp"

class PresidentialPardonForm : public Form
{
public:
	PresidentialPardonForm();
	PresidentialPardonForm(const std::string& target);
	PresidentialPardonForm(PresidentialPardonForm &cp);
	virtual ~PresidentialPardonForm();
	PresidentialPardonForm &operator=(const PresidentialPardonForm &op);

	void execute(const Bureaucrat &executor) const;
	const std::string &getTarget() const;
private:
	std::string target;

};


#endif //EX02_PRESIDENTIALPARDONFORM_HPP
