// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Far.cpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2022/02/24 17:00:14 by dzuntini          #+#    #+#             //
//   Updated: 2022/02/24 17:00:15 by dzuntini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Far.hpp"

Far::Far()
{

}

std::string Far::boucle(std::string const &line, std::string const &fnd, std::string const &repl)
{
	std::stringstream ss;
	size_t i, flen;

	flen = fnd.length();
	for (size_t j = 0;j < line.length();j++)
	{
		i = 0;
		while (line[i + j] == fnd[i] && i < flen)
			i++;
		if (i == flen)
		{
			ss << repl;
			j += i - 1;
		}
		else
			ss << line[j];
	}
	return(ss.str());
}

void Far::replace(std::string const &file, std::string const &fnd, std::string const &repl)
{
	std::ifstream origfile;
	std::ofstream repfile;
	std::string line;


	if (file.length() == 0)
		throw "File name empty";
	else if (fnd.length() == 0)
		throw "Find string empty";
	else if (repl.length() == 0)
		throw "Replace String empty";
	origfile.open(file);
	if (!origfile.good())
		throw "Cant open File";
	repfile.open(file + ".replace", std::ios::trunc); // Open a empty file always
	if (!repfile.is_open())
		throw "Cant open/create replace file";
	while (getline(origfile, line))
	{
		repfile << boucle(line, fnd, repl);
		if (!origfile.eof())
			repfile << "\n";
	}

}
