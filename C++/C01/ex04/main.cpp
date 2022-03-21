// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2022/02/24 16:30:53 by dzuntini          #+#    #+#             //
//   Updated: 2022/02/24 16:30:54 by dzuntini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //


#include "Far.hpp"

int main(int ac, char **av)
{
	if (ac == 4)

		try
		{
			Far::replace(av[1], av[2], av[3]);
		}
		catch(const char *e)
		{
			std::cerr << "Error : " << e << std::endl;
		}
	else
		std::cout <<"Error : Number of arguments"<< std::endl;
}
