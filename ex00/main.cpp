/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:56:04 by mpietrza          #+#    #+#             */
/*   Updated: 2025/09/03 17:04:12 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char **argv) {
	//check for correct usage
	if (argc != 2) {
		std::cout << "Error: could not open the file!" << std::endl;
		return 1;
	}

	//create BitcoinExchange object
	BitcoinExchange btc;

	//load the database - data.csv
	if (!btc.loadDatabase("data.csv")) {
		std::cout << "Error: could not open the database file!" << std::endl;
		return 1;
	}

	//process the input file (filename from commnd line input)
	btc.processInput(argv[1]);

	return 0;
}
