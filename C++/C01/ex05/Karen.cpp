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

#include "Karen.hpp"

void	Karen::complain( std::string level )
{
	void	(Karen::*complaint[])() =
			{
				&Karen::debug,
				&Karen::info,
				&Karen::warning,
				&Karen::error
			};
	std::string complaintLevels[] =
			{
			"debug",
			"info",
			"warning",
			"error"
			};

	for (int i = 0; i < 4; i++)
	{
		void (Karen::*selectedComplaint)() = complaint[i];
		if (level == complaintLevels[i])
			(this->*selectedComplaint)();

	}
}

void Karen::debug(void)
{
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do !\n";
}

void Karen::info(void)
{
	std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger ! If you did, I wouldn’t be asking for more !\n";
}

void Karen::warning(void)
{
	std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month.\n";
}

void Karen::error(void)
{
	std::cout << "This is unacceptable ! I want to speak to the manager now.\n";
}
