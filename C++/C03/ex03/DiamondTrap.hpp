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

#ifndef EX03_DIAMONDTRAP_HPP
#define EX03_DIAMONDTRAP_HPP

#include "ScavTrap.hpp"
#include "FragTrap.hpp"

class DiamondTrap :public ScavTrap , public FragTrap
{

private:
	std::string name;

public:
	DiamondTrap();
	explicit DiamondTrap(const std::string &name);
	DiamondTrap(DiamondTrap const &cp);
	~DiamondTrap();
	DiamondTrap &operator=(const DiamondTrap &op);
	void whoAmI();
	using ScavTrap::attack;
};


#endif //EX03_DIAMONDTRAP_HPP
