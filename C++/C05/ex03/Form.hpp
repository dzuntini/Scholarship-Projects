//
// Created by David Zuntini on 3/12/22.
//

#ifndef EX01_FORM_HPP
#define EX01_FORM_HPP

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

class Bureaucrat;

class Form
{
public:
	Form();
	Form(const std::string &name, int gradeToSign, int gradeToExec);
	Form(Form &cp);
	virtual ~Form();
	Form &operator=(const Form &op);

	void beSigned(const Bureaucrat& b);
	virtual void execute(Bureaucrat const & executor) const = 0;

	const std::string &getName() const;
	bool isSigned() const;
	int getGradeToSign() const;
	int getGradeToExec() const;
	void checkExecutability(const Bureaucrat &executor) const;

	class InvalidFormException : public std::exception
	{
	private:
		const char	*msg;
	public:
		InvalidFormException(void);
		InvalidFormException(const char *msg);
		const char* what() const throw();
	};

protected:
	const std::string name;
	bool is_signed;
	const int grade_to_sign;
	const int grade_to_exec;

private:
	class GradeTooHighException : public std::exception
	{
	private:
		const char	*msg;
	public:
		GradeTooHighException(void);
		GradeTooHighException(const char *msg);
		const char      *what() const throw();
	};
	class GradeTooLowException : public std::exception
	{
	private:
		const char	*msg;
	public:
		GradeTooLowException(void);
		GradeTooLowException(const char *msg);
		const char      *what() const throw();
	};
};

std::ostream &operator<<(std::ostream &os, const Form &form);

#endif //EX01_FORM_HPP
