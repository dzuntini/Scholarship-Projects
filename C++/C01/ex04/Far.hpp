// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Far.hpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2022/02/24 17:00:24 by dzuntini          #+#    #+#             //
//   Updated: 2022/02/24 17:00:25 by dzuntini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

//Find And Replace
#ifndef C_FAR_HPP
#define C_FAR_HPP

#include <iostream>
#include <fstream>
#include <sstream>

class Far
{
private:

public:
	Far();
	static void replace(std::string const &file, std::string const &find, std::string const &repl);
	static std::string boucle(std::string const &line, std::string const &fnd, std::string const &repl);
};

#endif //C_FAR_HPP
