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

#include "FragTrap.hpp"

FragTrap::FragTrap() :ClapTrap()
{
	std::cout << "FragTrap default constructor called" << std::endl;
	name = "Default";
	hit_points = 100;
	energy_points = 100;
	attack_damage = 30;
}

FragTrap::FragTrap(const std::string &name) : ClapTrap(name)
{
	std::cout << "Default constructor FragTrap called" << std::endl;
	this->name = name;
	hit_points = 100;
	energy_points = 100;
	attack_damage = 30;

}

FragTrap::FragTrap(const FragTrap &cp) : ClapTrap(cp)
{
	std::cout << "FragTrap Copy constructor called" << std::endl;
	name = cp.getName();
	hit_points = cp.getHitPoints();
	energy_points = cp.getEnergyPoints();
	attack_damage = cp.getAttackDamage();
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap Destructor called" << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &op)
{
	std::cout << "FragTrap Assignation operator called" << std::endl;
	name = op.getName();
	hit_points = op.getHitPoints();
	energy_points = op.getEnergyPoints();
	attack_damage = op.getAttackDamage();
	return (*this);
}


void FragTrap::highFiveGuys() const
{
	std::cout << "FragTrap " << name << " say : Give me a high five guys!" << std::endl;

}

void FragTrap::attack(const std::string &target)
{
	if (energy_points > 0 && hit_points > 0)
	{
		std::cout << "FragTrap " << name << " attacks " << target << " causing " << attack_damage << " points of damage !" << std::endl;
		energy_points--;
	}
	else
		std::cout << "FragTrap " << name << " can't attack cause it don't have enough energy or life !" << std::endl;
}



