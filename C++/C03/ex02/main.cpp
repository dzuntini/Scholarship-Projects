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

#include "ScavTrap.hpp"
#include "FragTrap.hpp"
int main()
{
	ScavTrap a(" CL4P-TP");
	FragTrap b("VR-0N1CA");
	a.attack("Himself");
	a.takeDamage(1);
	a.beRepaired(20);
	a.takeDamage(150);
	a.takeDamage(5);
	a.beRepaired(70);
	a.guardGate();
	b.attack("Himself");
	b.takeDamage(1);
	b.beRepaired(20);
	b.takeDamage(150);
	b.takeDamage(5);
	b.beRepaired(70);
	b.highFiveGuys();
	return (0);
}
