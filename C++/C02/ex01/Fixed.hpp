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

#ifndef C_FIXED_HPP
#define C_FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
private :
	int fix_val;
	static const int eight = 8;

public :
	Fixed();
	explicit Fixed(int);
	explicit Fixed(float);
	Fixed(Fixed const &cp);
	virtual ~Fixed();

	Fixed &operator = (Fixed const &op);

	float toFloat() const;
	int toInt() const;
	int getRawBits() const;
	void setRawBits(int raw);
};
std::ostream &operator<<(std::ostream &out, Fixed const &val);

#endif //C_FIXED_HPP
