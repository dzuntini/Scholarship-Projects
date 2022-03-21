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


#include "HumanB.hpp"

HumanB::HumanB(std::string const &name): name(name), weapon(nullptr)
{
}

void HumanB::setWeapon(const Weapon &weapon)
{
	this->weapon = &weapon;
}

void HumanB::attack() const
{
	if (this->weapon)
		std::cout << this->name << " hit you with " << this->weapon->getType() << std::endl;
	else
		std::cout << this->name << " can't attack you because he has no Weapon !" << std::endl;
}
