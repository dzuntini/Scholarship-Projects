//
// Created by David Zuntini on 3/15/22.
//

#ifndef EX02_SHRUBBERYCREATIONFORM_HPP
#define EX02_SHRUBBERYCREATIONFORM_HPP

#include <fstream>
#include "Form.hpp"

class ShrubberyCreationForm : public Form
{
public:
	ShrubberyCreationForm();
	ShrubberyCreationForm(ShrubberyCreationForm &cp);
	ShrubberyCreationForm(const std::string &target);
	virtual ~ShrubberyCreationForm();
	ShrubberyCreationForm &operator=(const ShrubberyCreationForm &op);

	void execute(const Bureaucrat &executor) const;
	const std::string &getTarget() const;
private:
	std::string target;



};


#endif //EX02_SHRUBBERYCREATIONFORM_HPP
