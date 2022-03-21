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


#ifndef C_ZOMBIE_HPP
#define C_ZOMBIE_HPP

#include <iostream>

class Zombie
{
public:

	Zombie(void);
	~Zombie(void);

	void announce(void);
	Zombie(std::string name);


	void setname(std::string name);

private:

	std::string name;
};

Zombie* newZombie(std::string name);
void randomChump(std::string name);

#endif //C_ZOMBIE_HPP
