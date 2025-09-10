/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosz <milosz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:58:22 by mpietrza          #+#    #+#             */
/*   Updated: 2025/09/10 17:45:14 by milosz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sys/time.h> //for gettimeofday

int main(int argc, char **argv) {
	PmergeMe pmergme;
	if (!pmergme.fillContainers(argc, argv)) {
		std::cout << "Error in given arguments!" << std::endl
				  << "argument is: " << argv[1] << std::endl;
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
