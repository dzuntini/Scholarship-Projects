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

ScavTrap::ScavTrap() :ClapTrap()
{
	std::cout << "ScavTrap default constructor called" << std::endl;
	name = "Default";
	hit_points = 100;
	energy_points = 50;
	attack_damage = 20;
}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name)
{
	std::cout << "Default constructor ScavTrap called" << std::endl;
	this->name = name;
	hit_points = 100;
	energy_points = 50;
	attack_damage = 20;

}

ScavTrap::ScavTrap(const ScavTrap &cp) : ClapTrap(cp)
{
	std::cout << "ScavTrap Copy constructor called" << std::endl;
	name = cp.getName();
	hit_points = cp.getHitPoints();
	energy_points = cp.getEnergyPoints();
	attack_damage = cp.getAttackDamage();
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap Destructor called" << std::endl;
}


ScavTrap &ScavTrap::operator=(const ScavTrap &op)
{
	std::cout << "ScavTrap Assignation operator called" << std::endl;
	name = op.getName();
	hit_points = op.getHitPoints();
	energy_points = op.getEnergyPoints();
	attack_damage = op.getAttackDamage();
	return (*this);
}

void ScavTrap::guardGate() const
{
	std::cout << "ScavTrap " << name << " enterred in gate keeper mode!" << std::endl;

}

void ScavTrap::attack(const std::string &target)
{
	if (energy_points > 0 && hit_points > 0)
	{
		std::cout << "ScavTrap " << name << " attacks " << target << " causing " << attack_damage << " points of damage !" << std::endl;
		energy_points--;
	}
	else
		std::cout << "ScavTrap " << name << " can't attack cause it don't have enough energy or life !" << std::endl;
}



