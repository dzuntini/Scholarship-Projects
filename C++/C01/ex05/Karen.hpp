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


#ifndef C_KAREN_HPP
#define C_KAREN_HPP

#include <string>
#include <iostream>

class Karen
{
public:
 void complain(std::string level );

private:
	void debug();
	void info();
	void warning();
	void error();
};


#endif //C_KAREN_HPP
