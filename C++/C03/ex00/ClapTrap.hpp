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

#ifndef EX00_CLAPTRAP_HPP
#define EX00_CLAPTRAP_HPP

#include <iostream>

class ClapTrap
{
private:


	std::string name;
	int hit_points;
	int energy_points;
	int attack_damage;
public:
	ClapTrap();
	explicit ClapTrap(const std::string &name);
	ClapTrap(ClapTrap const &cp);
	virtual ~ClapTrap();

	ClapTrap &operator=(const ClapTrap &op);

	void attack(const std::string& target);
	void takeDamage(unsigned int amount);
	void beRepaired(unsigned int amount);

	const std::string &getName() const;
	int getHitPoints() const;
	int getEnergyPoints() const;
	int getAttackDamage() const;

	void setHitPoints(int hitPoints);
	void setName(const std::string &name);
	void setEnergyPoints(int energyPoints);
	void setAttackDamage(int attackDamage);


};

#endif //EX00_CLAPTRAP_HPP
