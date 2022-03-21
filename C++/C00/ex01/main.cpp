// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp	                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2021/12/16 03:56:12 by dzuntini          #+#    #+#             //
//   Updated: 2021/12/16 03:56:13 by dzuntini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //


#include "PhoneBook.hpp"

bool isNumber(const std::string s)
{
	if (s.empty())
		return (false);
	for(int i = 0; i < (int)s.length(); i++)
	{
		if (std::isdigit(s[i]) == 0)
			return (false);
	}
	return (true);
}

int main()
{
	PhoneBook *pb  = new PhoneBook;
	std::string input;
	while (true)
	{
		std::cout << "GIMME one of thoses commands :\n";
		std::cout << "ADD - to add a contact :\n";
		std::cout << "SEARCH - to search someone :\n";
		std::cout << "EXIT - to GTFO :\n";

		std::cin >> input;
		if (input == "ADD")
		{
			if (pb->getCurrentIndex() < MAX)
				pb->set_info_contact();
			else
				std::cout << "Contact full , get lost!\n";
		}
		if (input == "SEARCH")
		{
			pb->show_contacts();
			std::cin >> input;
			if (!isNumber(input))
				std::cout << "Not a Number" << std::endl;
			else
				pb->show_contact(std::stoi(input));
		}
		if (input == "EXIT")
		{
			delete pb;
			break;
		}
	}
	return (0);
}