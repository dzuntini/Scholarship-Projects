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

#include "ClapTrap.hpp"

int main()
{
	ClapTrap a("Idiot");

	a.attack("Himself");
	a.takeDamage(1);
	a.beRepaired(20);
	a.takeDamage(10);
	a.takeDamage(5);
	a.beRepaired(200);
	for (int i = 0;i < 50;i++)
		a.attack("Himself");
	for (int i = 0;i < 20;i++)
		a.takeDamage(2);

	return (0);
}
