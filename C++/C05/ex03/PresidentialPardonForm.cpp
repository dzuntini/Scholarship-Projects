//
// Created by David Zuntini on 3/15/22.
//

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm()
		: Form("PresidentialPardonForm", 25, 5), target("")
{
}
PresidentialPardonForm::PresidentialPardonForm(const std::string& target)
		: Form("PresidentialPardonForm", 25, 5), target(target)
{
}


PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm &cp)
		: Form("PresidentialPardonForm", 25, 5), target(cp.getTarget())
{
}


PresidentialPardonForm::~PresidentialPardonForm()
{
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &op)
{
this->is_signed = op.is_signed;
return(*this);
}

void PresidentialPardonForm::execute(const Bureaucrat& executor) const
{
	this->checkExecutability(executor);
	std::cout << this->target << " has been pardoned by Zafod Beeblebrox." << std::endl;
}

const std::string &PresidentialPardonForm::getTarget() const
{
	return target;
}

