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

#ifndef EX01_FRAGTRAP_HPP
#define EX01_FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap : public virtual  ClapTrap
{
public:
	FragTrap();
	explicit FragTrap(const std::string &name);
	FragTrap(FragTrap const &cp);
	~FragTrap();
	FragTrap &operator=(const FragTrap &op);
	void	attack(std::string const & target);
	void highFiveGuys() const;
};


#endif //EX01_FRAGTRAP_HPP
