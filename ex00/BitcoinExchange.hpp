/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:31:15 by mpietrza          #+#    #+#             */
/*   Updated: 2025/08/11 19:12:16 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stdlib.h>
#include <limits>

class BitcoinExchange {
	private:
		std::map<std::string, double> _database;
		
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);

	public:
		BitcoinExchange();
		~BitcoinExchange();

		// Loads the bitcoin price database from a CSV file
		bool loadDatabase(const std::string &filename);

		// Process the input file and print results
		void processInput(const std::string &filename);

		// Check if date is in valid format (string YYYY-MM-DD)
		static bool isValidDate(const std::string &date);

		// Check if value is in valid format (float or int, 0 <= value <= 1000)
		static bool isValidValue(const std::string &value);

		// Getter - closest lower date's rate
		double getRate(const std::string &date) const;
};

#endif
