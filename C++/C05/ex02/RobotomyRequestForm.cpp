//
// Created by David Zuntini on 3/15/22.
//

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm()
		: Form("RobotomyRequestForm", 72, 45), target("")
{
}
RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
		: Form("RobotomyRequestForm", 72, 45), target(target)
{
}


RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm &cp)
		: Form("RobotomyRequestForm", 72, 45), target(cp.getTarget())
{
}


RobotomyRequestForm::~RobotomyRequestForm()
{
}


RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &op)
{
	this->is_signed = op.is_signed;
	return(*this);
}

const std::string &RobotomyRequestForm::getTarget() const
{
	return target;
}

void RobotomyRequestForm::execute(const Bureaucrat &executor) const
{
	static int i = 0;
	this->checkExecutability(executor);
	i++;
	std::cout << "Piercing Sounds are being heard" << std::endl;
	if (i % 2)
		std::cout << "Operation success : Completion of "<< this->target <<" robotomy" << std::endl;
	else
		std::cout << "Operation failure : Death of "<< this->target << std::endl;

}
