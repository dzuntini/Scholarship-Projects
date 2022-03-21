// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PhoneBook.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2022/02/01 13:03:01 by dzuntini          #+#    #+#             //
//   Updated: 2022/02/07 16:15:30 by dzuntini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
{
	this->contacts = new Contact[8];
	this->currentIndex = 0;
	this->nb = 0;
}

PhoneBook::~PhoneBook()
{
		delete[] this->contacts;
}

void    PhoneBook::add_contact(const std::string& first_name, const std::string last_name, const std::string nickname,
							   const std::string &phone_number, const std::string darkest_secret)
{
	this->contacts[currentIndex].setIndex(this->currentIndex);
	this->contacts[currentIndex].setFname(first_name);
	this->contacts[currentIndex].setLname(last_name);
	this->contacts[currentIndex].setNick(nickname);
	this->contacts[currentIndex].setPhnum(phone_number);
	this->contacts[currentIndex].setDksec(darkest_secret);
	if (this->nb < 8)
		this->nb++;
	this->currentIndex++;
}

int PhoneBook::getCurrentIndex() const
{
	return currentIndex;
}

std::string PhoneBook::ft_trcuncate(std::string s)
{
	if (s.length() > 10)
	{
		s.resize(9);
		s.append(".");
	}
	return (s);
}

void    PhoneBook::show_contacts() const
{
	std::cout << std::setw(10) << "index" << "|";
	std::cout << std::setw(10) << "first name" << "|";
	std::cout << std::setw(10) << "last name" << "|";
	std::cout << std::setw(10) << "nickname" << std::endl;
	for (int i = 0; i < this->nb ; i++)
	{
		std::cout << std::setw(10) << this->contacts[i].getIndex() << "|";
		std::cout << std::setw(10) << ft_trcuncate(this->contacts[i].getFname()) << "|";
		std::cout << std::setw(10) << ft_trcuncate(this->contacts[i].getLname()) << "|";
		std::cout << std::setw(10) << ft_trcuncate(this->contacts[i].getNick()) << std::endl;
	}
	std::cout << std::endl;
}

void    PhoneBook::show_contact(int index) const
{
	if (index >= this->nb || index < -1)
		std::cout << "\nNo Number Found with " << index << std::endl;
	else
	{
		std::cout << "\nfirst name:    " << this->contacts[index].getFname() << std::endl;
		std::cout << "last name   :    " << this->contacts[index].getLname() << std::endl;
		std::cout << "nickname    :    " << this->contacts[index].getNick() << std::endl;
		std::cout << "phone_number :   " << this->contacts[index].getPhnum() << std::endl;
		std::cout << "darkest_secret : " << this->contacts[index].getDksec() << std::endl;
		std::cout << std::endl;
	}
}

void    PhoneBook::set_info_contact()
{
	std::string first_name, last_name, nickname, phone_number, darkest_secret;
	std::cout << "\nfirst name = "; std::cin >> first_name;
	std::cout << "last name = "; std::cin >> last_name;
	std::cout << "nickname = "; std::cin >> nickname;
	std::cout << "phone_number = "; std::cin >> phone_number;
	std::cout << "darkest_secret = "; std::cin >> darkest_secret;
	add_contact(first_name, last_name, nickname, phone_number, darkest_secret);
	std::cout << "\nContact Added Successfully !\n" << std::endl;
}
