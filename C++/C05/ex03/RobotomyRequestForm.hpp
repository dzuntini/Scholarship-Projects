//
// Created by David Zuntini on 3/15/22.
//

#ifndef EX02_ROBOTOMYREQUESTFORM_HPP
#define EX02_ROBOTOMYREQUESTFORM_HPP

#include <iostream>
#include "Form.hpp"

class RobotomyRequestForm :public Form
{
public:
	RobotomyRequestForm();
	RobotomyRequestForm(RobotomyRequestForm &cp);
	RobotomyRequestForm(const std::string &target);
	virtual ~RobotomyRequestForm();
	RobotomyRequestForm &operator=(const RobotomyRequestForm &op);

	void execute(const Bureaucrat &executor) const;
private:
	std::string target;

	const std::string &getTarget() const;
};


#endif //EX02_ROBOTOMYREQUESTFORM_HPP
