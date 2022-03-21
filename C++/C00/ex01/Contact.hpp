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



#ifndef C_PHONEBOOK_H
#define C_PHONEBOOK_H

#include <string>
#include <iostream>
#include <iomanip>
#include <unistd.h>

#define MAX 	8
#define WIDTH	10

class Contact
{
public:
	const std::string &getFname() const;

	const std::string &getLname() const;

	const std::string &getNick() const;

	const std::string &getPhnum() const;

	const std::string &getDksec() const;

	void setFname(const std::string &fname);

	void setLname(const std::string &lname);

	void setNick(const std::string &nick);

	void setPhnum(const std::string &phnum);

	void setDksec(const std::string &dksec);

	int getIndex() const;

	void setIndex(int index);


private:
	int 		index;
	std::string fname;
	std::string lname;
	std::string nick;
	std::string phnum;
	std::string dksec;
};


#endif //C_PHONEBOOK_H
