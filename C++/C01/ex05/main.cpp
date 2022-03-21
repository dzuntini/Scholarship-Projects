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

int main()
{
	Karen conne;

	std::string complaintLevels[] =
			{
					"debug",
					"info",
					"warning",
					"error"
			};
	for (int i = 0;i < 4;i++)
	{
		std::cout << "LEVEL :[ " << complaintLevels[i] << " ]\n";
		conne.complain(complaintLevels[i]);
	}
}
