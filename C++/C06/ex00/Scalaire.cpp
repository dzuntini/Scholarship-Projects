//
// Created by David Zuntini on 3/15/22.
//


#include "Scalaire.hpp"

/*Coplien Cannonic Form */
Scalaire::Scalaire() {}

Scalaire::~Scalaire() {}

Scalaire::Scalaire(char  *target) : target(target)
{
	this->type = -1;
}

Scalaire::Scalaire(Scalaire &cp)
{
	*this = cp;
}

Scalaire &Scalaire::operator=(const Scalaire &op)
{
	this->target = op.target;
	this->type = op.type;
	return (*this);
}


bool			Scalaire::getType(void)
{
	this->type = handleSpecial(this->target);
	if (this->type != -1)
		return true;
	if (ft_isdigit(target[0]) || target[0] == '-' || target[0] == '.')
	{
		this->type = handleNumeric(this->target);
		if (this->type != -1)
			return true;
	}
	if (target[1])
		return false;
	this->type = 0;
	return true;
}

void 			Scalaire::print()
{
	getType();
	printchar();
	printint();
	printfloat();
	printdouble();
}

void			Scalaire::printchar(void)
{
	if (this->type == 1)
	{
		if (canConvertToChar(atoi(target)))
			std::cout << "char: " << static_cast<char>(atoi(target)) << std::endl;
	}
	else if (this->type == 2)
	{
		if (canConvertToChar(atof(target)))
			std::cout << "char: " << static_cast<char>(atof(target)) << std::endl;
	}
	else if (this->type == 3)
	{
		if (canConvertToChar(atof(target)))
			std::cout << "char: " << static_cast<char>(atof(target)) << std::endl;
	}
	else
		std::cout << "char: " << target << std::endl;
}

void			Scalaire::printint(void)
{
	if (this->type == 0)
		std::cout << "int: " << static_cast<int>(target[0]) << std::endl;

	else if (this->type == 1)
		std::cout << "int: " << atoi(target) << std::endl;

	else if (this->type == 2)
	{
		if (canConvertToInt(atof(target)))
			std::cout << "int: " << static_cast<int>(atof(target)) << std::endl;
		else
			std::cout << "int: impossible" << std::endl;
	}

	else if (this->type == 3)
	{
		if (canConvertToInt(atof(target)))
			std::cout << "int: " << static_cast<int>(atof(target)) << std::endl;
		else
			std::cout << "int: impossible" << std::endl;
	}
}

void			Scalaire::printfloat(void)
{
	if (this->type == 0)
		std::cout << "float: " << static_cast<float>(target[0]) << ".0f" << std::endl;

	else if (this->type == 1)
		std::cout << "float: " << static_cast<float>(atoi(target)) << ".0f"<< std::endl;

	else if (this->type == 2)
	{
		std::cout << "float: " << atof(target);
		std::cout<< dotZero(static_cast<float>(atof(target))) << "f" << std::endl;
	}

	else if (this->type == 3)
	{
		if (canConvertToFloat(atof(target)))
		{
			std::cout << "float: " << static_cast<float>(atof(target));
			std::cout<< dotZero(static_cast<double>(atof(target))) << "f" << std::endl;
		}
		else
			std::cout << "float: impossible" << std::endl;
	}
}

void			Scalaire::printdouble(void)
{
	if (this->type == 0)
		std::cout << "double: " << static_cast<double>(type) << ".0" << std::endl;

	else if (this->type == 1)
		std::cout << "double: " << static_cast<double>(atoi(target)) << ".0" << std::endl;

	else if (this->type == 2)
	{
		std::cout << "double: " << static_cast<double>(atof(target));
		std::cout << dotZero(static_cast<double>(atof(target))) << std::endl;
	}

	else if (this->type == 3)
	{
		std::cout << "double: " << atof(target);
		std::cout << dotZero(static_cast<double>(atof(target))) << std::endl;
	}
}
/*Getter/Setter*/

char*Scalaire::getTarget() const
{
	return target;
}

void Scalaire::setTarget(char*target)
{
	Scalaire::target = target;
}


/*Exception*/

Scalaire::InvalidInputException::InvalidInputException(void) : msg("Invalid input!") {}

Scalaire::InvalidInputException::InvalidInputException(const char *msg) : msg(msg) {}

const char	*Scalaire::InvalidInputException::what() const throw()
{
	return (this->msg);
}




/*Utils */

const char		*dotZero(double num)
{
	if (num - static_cast<int>(num) == 0.0)
		return (".0");
	return ("");
}

bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	canConvertToInt(double number)
{
	return (number <= std::numeric_limits<int>::max()
			&& number >= std::numeric_limits<int>::min()
			&& number != std::numeric_limits<double>::infinity()
			&& number != -std::numeric_limits<double>::infinity()
			&& number != std::numeric_limits<double>::quiet_NaN());
}

bool	canConvertToFloat(double number)
{
	return ((number <= std::numeric_limits<float>::max()
			 && number >= -std::numeric_limits<float>::max())
			|| number == std::numeric_limits<double>::infinity()
			|| number == -std::numeric_limits<double>::infinity()
			|| std::isnan(number));
}

bool	canConvertToChar(double number)
{
	if (number - static_cast<int>(number) != 0 || number > 127 || number < 0)
		std::cout << "char: impossible" << std::endl;

	else if (number <= 31 || number == 127)
		std::cout << "char: Non displayable" << std::endl;

	else
		return true;
	return false;
}

int		handleSpecial(const char *target)
{
	const char	*special_doubles[] =
			{
					"inf", "+inf", "-inf", "nan"
			};
	const char	*special_floats[] =
			{
					"inff", "+inff", "-inff", "nanf"
			};

	for (int i = 0; i < 4; i++)
	{
		if (!strcmp(special_floats[i], target))
			return (2);
		else if (!strcmp(special_doubles[i], target))
			return (3);
	}
	return (-1);
}

int		handleNumeric(const char *target)
{
	int	i;
	int	dots;

	i = 0;
	dots = 0;
	if (target[0] == '-' && target[1])
		i++;
	if (target[i] == '.' && (target[i + 1] == 'f' || target[i + 1] == 0))
		return (-1);
	while (target[i] == '.' || ft_isdigit(target[i]))
	{
		if (target[i] == '.')
			dots++;
		if (dots > 1)
			return (-1);
		i++;
	}
	if (!target[i])
	{
		if (dots == 1)
			return (3);
		return (1);
	}
	else if (target[i] == 'f' && !target[i + 1] && dots == 1)
		return (2);
	return (-1);
}

