//
// Created by David Zuntini on 2/1/22.
//

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include "Contact.hpp"

class PhoneBook {

private :
	Contact *contacts;
	int nb;
	int currentIndex;

public :
	PhoneBook();
	void    add_contact(const std::string&, std::string, std::string, const std::string&, std::string);
	static std::string ft_trcuncate(std::string) ;
	void    show_contact(int) const;
	void    show_contacts() const;
	void    set_info_contact();

	int getCurrentIndex() const;

	virtual ~PhoneBook();
};

#endif