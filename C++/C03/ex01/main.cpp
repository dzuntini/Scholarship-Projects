// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   C++                                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2021/12/16 03:56:12 by dzuntini          #+#    #+#             //
//   Updated: 2022/03/10 17:59:41 by dzuntini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ScavTrap.hpp"

int main()
{
	ScavTrap a("Idiot");

	a.attack("Himself");
	a.takeDamage(1);
	a.beRepaired(20);
	a.takeDamage(150);
	a.takeDamage(5);
	a.beRepaired(70);
	a.guardGate();
	return (0);
}
