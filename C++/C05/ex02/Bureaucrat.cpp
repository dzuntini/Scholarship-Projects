//
// Created by David Zuntini on 3/12/22.
//

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat()
{
}

Bureaucrat::Bureaucrat(const std::string  &name, int grade) : name(name)
{
	if (grade > 150)
		throw GradeTooLowException();
	else if (grade < 1)
		throw GradeTooHighException();
	this->grade = grade;
}

Bureaucrat::Bureaucrat(Bureaucrat &cp) :name(cp.name) , grade(cp.grade)
{
}

Bureaucrat::~Bureaucrat()
{
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &op)
{
	this->grade = op.grade;
	return (*this);
}

const std::string &Bureaucrat::getName() const
{
	return name;
}

int Bureaucrat::getGrade() const
{
	return grade;
}

void Bureaucrat::incrementGrade()
{
	if (this->grade == 1)
		throw  GradeTooHighException();
	this->grade--;
}

void Bureaucrat::decrementGrade()
{
	if (this->grade == 150)
		throw  GradeTooLowException();
	this->grade--;
}

void	Bureaucrat::signForm(Form& form)
{
	try
	{
		form.beSigned(*this);
		std::cout << "Bureaucrat " << this->name << " successfully signed ";
		std::cout << "the form " << form.getName() << "!" << std::endl;
	}
	catch(const std::exception &e)
	{
		std::cout << *this << ". ";
		std::cout << e.what() << std::endl;
	}
}

void Bureaucrat::executeForm(const Form &form)
{
	try
	{
		form.execute(*this);
		std::cout << this->name << " executes form " << form.getName() << std::endl;
	}
	catch (Form::InvalidFormException &e)
	{
		std::cout << e.what() << std::endl;
	}
}

std::ostream &operator<<(std::ostream &os, const Bureaucrat &bureaucrat)
{
	os << "name: " << bureaucrat.getName() << " grade: " << bureaucrat.getGrade() << std::endl;
	return os;
}

const char*Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Error: Grade Too High, Give number between 1-150";
}

const char*Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Error: Grade Too Low, Give number between 1-150";
}
