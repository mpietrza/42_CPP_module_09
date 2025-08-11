/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:22:16 by mpietrza          #+#    #+#             */
/*   Updated: 2025/08/11 19:11:53 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::loadDatabase(const std::string &filename) {
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		return false;

	std::string line;
	//skips the header line by doing getline and not using it
	std::getline(file, line);
	
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string date, rateStr;
		
		//parse date
		if (!std::getline(iss, date, ','))
			return false;

		//parse exchange rate 
		if (!std::getline(iss, rateStr))
			return false;
		
		//remove whitespaces
		date.erase(date.find_last_not_of(" \t\r\n") + 1);
		date.erase(0, date.find_first_not_of(" \t\r\n"));
		rateStr.erase(rateStr.find_last_not_of(" \t\r\n") + 1);
		rateStr.erase(0, rateStr.find_first_not_of(" \t\r\n"));

		//check the date
		if (!isValidDate(date))
			return false;
		
		//change string 'rateStr' to double 'rate'
		char *endptr;
		double rate = std::strtod(rateStr.c_str(), &endptr);
		if (endptr == rateStr)
			return false;
		
		//store in map
		_database[date] = rate;
	}
	return true;
}

