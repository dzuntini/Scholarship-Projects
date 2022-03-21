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

#include "DiamondTrap.hpp"


DiamondTrap::DiamondTrap()
{
	std::cout << "DiamondTrap default constructor called" << std::endl;
	name = "Default";
	ClapTrap::setName(name + "_clap_name");
	hit_points = FragTrap::hit_points;
	energy_points = ScavTrap::energy_points;
	attack_damage = FragTrap::attack_damage;
}

DiamondTrap::DiamondTrap(const std::string &name) : ClapTrap(name), ScavTrap(name), FragTrap(name)
{
	std::cout << "Default constructor DiamondTrap called" << std::endl;
	this->name = name;
	ClapTrap::setName(name + "_clap_name");
	hit_points = FragTrap::hit_points;
	energy_points = ScavTrap::energy_points;
	attack_damage = FragTrap::attack_damage;
}

DiamondTrap::DiamondTrap(const DiamondTrap &cp) : ClapTrap(cp), ScavTrap(cp), FragTrap(cp)
{
	*this = cp;
}


DiamondTrap &DiamondTrap::operator=(const DiamondTrap &op)
{
	std::cout << "DiamondTrap Assignation operator called" << std::endl;
	name = op.getName();
	ClapTrap::setName(name + "_clap_name");
	hit_points = op.getHitPoints();
	energy_points = op.getEnergyPoints();
	attack_damage = op.getAttackDamage();
	return (*this);
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap Destructor called" << std::endl;
}

void DiamondTrap::whoAmI()
{
	std::cout << "My name : " << this->name << ", and my ClapTrap name : " << ClapTrap::getName() << std::endl;
}
