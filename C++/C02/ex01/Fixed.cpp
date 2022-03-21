// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   C++                                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2021/12/16 03:56:12 by dzuntini          #+#    #+#             //
//   Updated: 2022/02/07 15:43:53 by dzuntini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Fixed.hpp"

Fixed::Fixed()
{
	fix_val = 0;
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(Fixed const &cp)
{
	std::cout << "Copy constructor called" << std::endl;
	std::cout << "Copy assignation operator called" << std::endl;
	fix_val = cp.getRawBits();
}

Fixed::Fixed(const int value)
{
	std::cout << "Int constructor called" << std::endl;
	fix_val = (value << Fixed::eight);
}

Fixed::Fixed(const float value)
{
	std::cout << "Float constructor called" << std::endl;
	fix_val = roundf(value * (1 << Fixed::eight));
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}


Fixed &Fixed::operator=(const Fixed &op)
{
	std::cout << "Copy assignation operator called" << std::endl;
	fix_val = op.getRawBits();
	return (*this);
}

std::ostream &operator<<(std::ostream &out, Fixed const &val)
{
	out << val.toFloat();
	return (out);
}

int Fixed::getRawBits() const
{
	return (fix_val);
}

void Fixed::setRawBits(const int raw)
{
	fix_val = raw;
}

float Fixed::toFloat() const
{
	return ((float)fix_val / (float)(1 << Fixed::eight));
}

int	Fixed::toInt() const
{
	return (fix_val >> Fixed::eight);
}
