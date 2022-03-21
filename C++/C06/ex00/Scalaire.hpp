//
// Created by David Zuntini on 3/15/22.
//

#ifndef EX00_SCALAIRE_HPP
#define EX00_SCALAIRE_HPP

#include <iostream>
#include <cstdlib>
#include <cmath>

class Scalaire
{
public:
	Scalaire();
	Scalaire(Scalaire &cp);
	Scalaire(char *target);
	Scalaire &operator=(const Scalaire &op);
	virtual ~Scalaire();

	void convert();

	void print();
	void printchar();
	void printint();
	void printfloat();
	void printdouble();


private:
	char *target;
	int type; // -1 No type , Char 0 , Int 1 , Float 2 , Double 3


public:
	char*getTarget() const;

	void setTarget(char*target);

public:
	class InvalidInputException : public std::exception
	{
	private:
		const char	*msg;
	public:
		InvalidInputException();
		InvalidInputException(const char *msg);

		virtual const char	*what() const throw();
	};

	bool getType(void);
};

bool	ft_isdigit(char c);
bool	canConvertToInt(double number);
bool	canConvertToFloat(double number);
bool	canConvertToChar(double number);
const char		*dotZero(double num);
int		handleSpecial(const char *target);
int		handleNumeric(const char *target);
#endif //EX00_SCALAIRE_HPP
