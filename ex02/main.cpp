/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosz <milosz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:58:22 by mpietrza          #+#    #+#             */
/*   Updated: 2025/09/12 11:46:14 by milosz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sys/time.h> //for gettimeofday

int main(int argc, char **argv) {
	if (argc == 2) {
		int i = 0;
		bool oneArg = true;
		while (argv[1][i]) {
			if (argv[1][i] < '1' || argv[1][i] > '9') {
				std::cout << "Error in given arguments!" << std::endl
						  << "argument is: " << argv[1][i] << std::endl;
				return 1;
			}
			if (argv[1][i] == ' ' && argv[i + 1] && argv[1][i + 1] != ' ')
				oneArg = false;
			i++;
		}
		if (oneArg == true)
		std::cout << "Only one argument: " << argv[1] << ", so there is nothing to sort!" << std::endl;
		return 0;
	}

	PmergeMe pmergme;
	int errPos = pmergme.fillContainers(argc, argv);
	if (errPos != TRUE) {
		std::cout << "Error in given arguments!" << errPos  << std::endl;
		if (errPos != FALSE)
			std::cout  << "argument is: " << argv[1][errPos] << std::endl;
		return 1;
	}
	pmergme.printBefore();

	struct timeval tv;
	gettimeofday(&tv, NULL);
	pmergme.setStartVector(tv);
	pmergme.fordJohnsonSortVector(pmergme.getVector(), 0, pmergme.getVectorSize());
	gettimeofday(&tv, NULL);
	pmergme.setEndVector(tv);

	gettimeofday(&tv, NULL);
	pmergme.setStartDeque(tv);
	pmergme.fordJohnsonSortDeque(pmergme.getDeque(), 0, pmergme.getDequeSize());
	gettimeofday(&tv, NULL);
	pmergme.setEndDeque(tv);
	
	pmergme.printAfter();
	pmergme.printTimes();
}
