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


#ifndef C_HUMANA_HPP
#define C_HUMANA_HPP

#include "Weapon.hpp"

class HumanA
{
public:
	HumanA(const std::string &name, const Weapon &weap);

	void attack() const;


private:
	const Weapon &weap;
	std::string name;
	std::string weap_t;

};


#endif //C_HUMANA_HPP
