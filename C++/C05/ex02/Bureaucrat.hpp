//
// Created by David Zuntini on 3/12/22.
//

#ifndef EX00_BUREAUCRAT_HPP
#define EX00_BUREAUCRAT_HPP

#include "Form.hpp"
#include <iostream>

class Form;

class Bureaucrat
{
public:
	Bureaucrat();
	Bureaucrat(Bureaucrat &cp);
	Bureaucrat(const std::string &name, int grade);
	virtual ~Bureaucrat();
	Bureaucrat &operator=(const Bureaucrat &op);

	void incrementGrade();
	void decrementGrade();
	void signForm(Form &form);
	void executeForm(Form const & form);
private:
	const std::string name;
	int grade;


public:
	const std::string &getName() const;
	int getGrade() const;

private:
	class GradeTooHighException : public std::exception
	{
	public:
		const char *what() const throw();
	};
	class GradeTooLowException : public std::exception
	{
	public:
		const char* what() const throw();
	};


};
std::ostream &operator<<(std::ostream &os, const Bureaucrat &bureaucrat);

#endif //EX00_BUREAUCRAT_HPP
