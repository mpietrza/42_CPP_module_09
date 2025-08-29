/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:22:16 by mpietrza          #+#    #+#             */
/*   Updated: 2025/08/29 14:50:20 by mpietrza         ###   ########.fr       */
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
		
		//remove whitespaces in the beginning and end of the strings
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

void BitcoinExchange::processInput(const std::string &filename){
	std::ifstream file(filename.c_str());
	if (!file.is_open()) {
		std::cout << "Error: could not open the file." << std::endl;
		return;
	}

	std::string line;
	//next line skips header again like in loadDatabase
	std::getline(file,line);

	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string date, valueStr;

		//parse date
		if (!std::getline(iss, date, '|')) {
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		
		//remove whitespace in the beginning and the end of the strings
		date.erase(date.find_last_not_of(" \t\r\n") + 1);
		date.erase(0, date.find_first_not_of(" \t\r\n"));
		valueStr.erase(valueStr.find_last_not_of(" \t\r\n") + 1);
		valueStr.erase(0, valueStr.find_first_not_of(" \t\r\n"));

		//Validate date
		if (!isValidDate(date)) {
			std::cout << "Error: bad input => " << date << std::endl;
			continue;
		}
		
		//validate value
		if (!isValidValue(valueStr)) {
			std::cout << "Error: bad input => " << valueStr << std::endl;
			continue;
		}
		
		//convert value to double and check it again
		double value = std::strtod(valueStr.c_str(), NULL);
		if (value < 0) {
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000) {
			std::cout << "Error: too large number." << std::endl;
			continue;
		}

		double rate = getRate(date);
		std::cout << date << " => " << value << " = " << value * rate << std::endl;
	}
}
