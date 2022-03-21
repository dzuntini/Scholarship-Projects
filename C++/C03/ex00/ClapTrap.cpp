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

ClapTrap::ClapTrap()
{
	std::cout << "ClapTrap default constructor called" << std::endl;
	name = "Default";
	hit_points = 10;
	energy_points = 10;
	attack_damage = 0;
}

ClapTrap::ClapTrap(const std::string& name) : name(name)
{
	std::cout << "ClapTrap constructor called" << std::endl;
	hit_points = 10;
	energy_points = 10;
	attack_damage = 0;
}

ClapTrap::ClapTrap(ClapTrap const &cp)
{
	std::cout << "ClapTrap Copy constructor called" << std::endl;
	name = cp.getName();
	hit_points = cp.getHitPoints();
	energy_points = cp.getEnergyPoints();
	attack_damage = cp.getAttackDamage();
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap Destructor called" << std::endl;
}


ClapTrap &ClapTrap::operator=(const ClapTrap &op)
{
	std::cout << "ClapTrap Assignation operator called" << std::endl;
	name = op.getName();
	hit_points = op.getHitPoints();
	energy_points = op.getEnergyPoints();
	attack_damage = op.getAttackDamage();
	return (*this);
}

void ClapTrap::attack(const std::string &target)
{
	if (energy_points > 0 && hit_points > 0)
	{
		std::cout << "ClapTrap " << name << " attacks " << target << " causing " << attack_damage << " points of damage !" << std::endl;
		energy_points--;
	}
	else
		std::cout << "ClapTrap " << name << " can't attack cause it don't have enough energy or life !" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	if (hit_points > 0)
	{
		hit_points = hit_points - amount;
		if (hit_points <= 0)
		{
			std::cout << "ClapTrap " << name << "is destroyed !" << std::endl;
			hit_points = 0;
		}
		else
		std::cout << "ClapTrap " << name << " take  " << amount << " points of damage !" << " Life left : " << hit_points << std::endl;
	}
	else
		std::cout << "ClapTrap " << name << " is already destroyed!" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (energy_points > 0 && hit_points > 0)
	{
		std::cout << "ClapTrap " << name << " repair " << amount << "life points back ! Life left :" << hit_points << std::endl;
		hit_points = hit_points + amount;
		energy_points--;
	}
	else
		std::cout << "ClapTrap " << name << "can't repair itself cause it don't have enough energy or life!" << std::endl;

}

const std::string &ClapTrap::getName() const
{
	return name;
}

void ClapTrap::setName(const std::string &name)
{
	ClapTrap::name = name;
}

int ClapTrap::getHitPoints() const
{
	return hit_points;
}

void ClapTrap::setHitPoints(int hitPoints)
{
	hit_points = hitPoints;
}

int ClapTrap::getEnergyPoints() const
{
	return energy_points;
}

void ClapTrap::setEnergyPoints(int energyPoints)
{
	energy_points = energyPoints;
}

int ClapTrap::getAttackDamage() const
{
	return attack_damage;
}

void ClapTrap::setAttackDamage(int attackDamage)
{
	attack_damage = attackDamage;
}

