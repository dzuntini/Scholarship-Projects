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


#ifndef C_WEAPON_HPP
#define C_WEAPON_HPP

#include <iostream>
#include <string>

class Weapon
{
public:
	Weapon();

	std::string const &getType(void) const;
	void setType(const std::string &type);

	Weapon(const std::string &type);

private:
	std::string type;

};


#endif //C_WEAPON_HPP
