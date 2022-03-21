// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Phonebook.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2021/12/16 03:56:12 by dzuntini          #+#    #+#             //
//   Updated: 2021/12/16 03:56:13 by dzuntini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //


#include "Contact.hpp"

int Contact::getIndex() const
{
	return index;
}



const std::string &Contact::getFname() const
{
	return fname;
}

const std::string &Contact::getLname() const
{
	return lname;
}

const std::string &Contact::getNick() const
{
	return nick;
}

const std::string &Contact::getPhnum() const
{
	return phnum;
}

const std::string &Contact::getDksec() const
{
	return dksec;
}

void Contact::setIndex(int index)
{
	Contact::index = index;
}

void Contact::setFname(const std::string &fname)
{
	Contact::fname = fname;
}

void Contact::setLname(const std::string &lname)
{
	Contact::lname = lname;
}

void Contact::setNick(const std::string &nick)
{
	Contact::nick = nick;
}

void Contact::setPhnum(const std::string &phnum)
{
	Contact::phnum = phnum;
}

void Contact::setDksec(const std::string &dksec)
{
	Contact::dksec = dksec;
}
