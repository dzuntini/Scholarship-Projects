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
	fix_val = cp.getRawBits();
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}


Fixed &Fixed::operator=(const Fixed &op)
{
	std::cout << "Assignation operator called" << std::endl;
	fix_val = op.getRawBits();
	return (*this);
}

int Fixed::getRawBits(void) const
{
	return (fix_val);
}

void Fixed::setRawBits(const int raw)
{
	fix_val = raw;
}
