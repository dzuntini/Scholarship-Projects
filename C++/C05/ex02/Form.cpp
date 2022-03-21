//
// Created by David Zuntini on 3/12/22.
//

#include "Form.hpp"


Form::Form() : name(), is_signed(false), grade_to_sign(1), grade_to_exec(1)
{}

Form::Form(const std::string &name, const int gradeToSign, const int gradeToExec) : name(name),
grade_to_sign(gradeToSign), grade_to_exec(gradeToExec)
{
	if (gradeToExec > 150 || gradeToSign > 150)
		throw GradeTooLowException();
	if (gradeToSign < 1 || gradeToExec < 1)
		throw GradeTooHighException();
	this->is_signed = false;
}

Form::Form(Form &cp) : name(cp.name), is_signed(cp.is_signed), grade_to_sign(cp.grade_to_sign), grade_to_exec(cp.grade_to_exec)
{
}

Form::~Form()
{
}

Form &Form::operator=(const Form &op)
{
	this->is_signed = op.is_signed;
	return (*this);
}

void				Form::beSigned(const Bureaucrat& b)
{
	if (b.getGrade() > this->grade_to_sign)
		throw GradeTooLowException("Bureaucrat is not authorized to sign the form!");
	this->is_signed = true;
}

void				Form::checkExecutability(const Bureaucrat& executor) const
{
	if (executor.getGrade() > grade_to_exec)
		throw GradeTooLowException("Bureaucrat is not authorized to execute the form!");
	if (!this->is_signed)
		throw InvalidFormException("Not signed forms cannot be executed!");
}


const std::string &Form::getName() const
{
	return name;
}

bool Form::isSigned() const
{
	return is_signed;
}

int Form::getGradeToSign() const
{
	return grade_to_sign;
}

int Form::getGradeToExec() const
{
	return grade_to_exec;
}



std::ostream &operator<<(std::ostream &os, const Form &form)
{
	os << "name: " << form.getName() << " is signed: " << (form.isSigned() ? "true" : "false") << " grade to sign: " << form.getGradeToSign()
	   << " grade to exec: " << form.getGradeToExec();
	return os;
}


Form::GradeTooHighException::GradeTooHighException()
{
	this->msg = "The grade is higher than the maximum!";
}

Form::GradeTooHighException::GradeTooHighException(const char *msg) : msg(msg) {}

const char	*Form::GradeTooHighException::what() const throw()
{
	return (this->msg);
}

Form::GradeTooLowException::GradeTooLowException()
{
	this->msg = "The grade is lower than the minimum!";
}

Form::GradeTooLowException::GradeTooLowException(const char *msg) : msg(msg) {}

const char	*Form::GradeTooLowException::what() const throw()
{
	return (this->msg);
}

Form::InvalidFormException::InvalidFormException()
{
	this->msg = "The form cannot be executed!";
}

Form::InvalidFormException::InvalidFormException(const char *msg) : msg(msg) {}

const char	*Form::InvalidFormException::what() const throw()
{
	return (this->msg);
}
