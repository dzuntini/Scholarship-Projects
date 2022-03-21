//
// Created by David Zuntini on 3/15/22.
//

#include <fstream>
#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm()
		: Form("ShrubberyCreationForm", 145, 137), target("")
{
}
ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
		: Form("ShrubberyCreationForm", 145, 137), target(target)
{
}


ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm &cp)
		: Form("ShrubberyCreationForm", 145, 137), target(cp.getTarget())
{
}


ShrubberyCreationForm::~ShrubberyCreationForm()
{
}


const std::string &ShrubberyCreationForm::getTarget() const
{
	return target;
}


ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &op)
{
	this->is_signed = op.is_signed;
	return(*this);
}

void ShrubberyCreationForm::execute(const Bureaucrat &executor) const
{
	std::ofstream	file;
	std::string		name;

	this->checkExecutability(executor);
	name = target + "_shrubbery";
	file.open(name.c_str(), std::ofstream::out);
	file << "        _-_      " << std::endl;
	file << "	  /~~ ~~\\   " << std::endl;
	file << "     /~~   ~~\\  " << std::endl;
	file << "    {  TREES  }  " << std::endl;
	file << "     \\ _-  -_ /   " << std::endl;
	file << "     ~  \\ /  ~  " << std::endl;
	file << " _- -   | | _- _ " << std::endl;
	file << "	_ - | |   -_ " << std::endl;
	file << "	    / \\     " << std::endl;



}

