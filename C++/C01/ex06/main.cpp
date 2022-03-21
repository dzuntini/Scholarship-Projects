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

int main(int ac, char **av)
{
	if (ac == 2)
	{
		Karen conne;
		std::string str(av[1]);
		std::transform(str.begin(), str.end(),str.begin(), ::toupper);
		conne.complain(str);
	}
}
