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

class Fixed
{
private :
	int fix_val;
	static const int eight = 8;
public :

	Fixed();
	Fixed(Fixed const &cp);
	virtual ~Fixed();

	Fixed &operator = (Fixed const &op);

	int getRawBits( void ) const;
	void setRawBits( int const raw );
};


#endif //C_FIXED_HPP
