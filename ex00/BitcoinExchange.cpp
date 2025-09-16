/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:22:16 by mpietrza          #+#    #+#             */
/*   Updated: 2025/09/16 15:07:41 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _database(other._database) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
	if (this != &other) {
		_database = other._database;
	}
	return *this;
}

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
		if (!std::getline(iss, valueStr)) {
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

static std::string getCurrentDate() {
	std::time_t t = std::time(NULL);
	std::tm tm = *std::localtime(&t);
	std::ostringstream oss;
	oss << std::setfill('0') << std::setw(4) << (tm.tm_year + 1900) << "-"
		<< std::setw(2) << (tm.tm_mon + 1) << "-"
		<< std::setw(2) << tm.tm_mday;
	return oss.str();
}

static bool checkIfNotInFuture(const std::string&date) {
	std::string today = getCurrentDate();
	return date <= today;
}	

bool BitcoinExchange::isValidDate(const std::string &date) {
	if (date.length() != 10) 
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;
	int year, month, day;
	char dash1, dash2;
	std::istringstream iss(date);
	if (!(iss >> year >> dash1 >> month >> dash2 >> day))
		return false;
	if (dash1 != '-' || dash2 != '-')
		return false;
	if (year < 2009) {
		std::cout << "Error: Bitcoin started in 2009! ";
		return false;
	}
	if (!checkIfNotInFuture(date)) {
		std::cout << "Error: the date is in the future! ";
		return false;
	}
	if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12 ) && (day > 31))
		return false;
	else if ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30))
		return false;
	else if ((!((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) && (month == 2 && day > 29))
		return false;
	else if (month == 2 && day > 28)
		return false;
	return true;
}

bool BitcoinExchange::isValidValue(const std::string &valueStr) {
	char *endptr;
	double value = std::strtod(valueStr.c_str(), &endptr);
	if (endptr == valueStr.c_str())
		return false;
	if (value < 0) {
		std::cout << "Error: not a positive number." << std::endl;
		return false;
	}
	if (value > 1000) {
		std::cout << "Error: too large number." << std::endl;
		return false;
	}
	return true;
}

double BitcoinExchange::getRate(const std::string &date) const {
	std::map<std::string, double>::const_iterator it = _database.find(date);
	if (it != _database.end())
		return it->second;

	it = _database.lower_bound(date);
	if (it == _database.begin())
		return 0.0;
	if (it == _database.end() || it->first != date)
		--it;
	return it->second;
}
