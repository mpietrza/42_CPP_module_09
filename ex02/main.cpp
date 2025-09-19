/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:58:22 by mpietrza          #+#    #+#             */
/*   Updated: 2025/09/19 15:26:35 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sys/time.h> //for gettimeofday

int main(int argc, char **argv) {
	struct timeval tv;
	PmergeMe pmergeme;
	
	gettimeofday(&tv, NULL);
	pmergeme.setStart(tv, PARSE);

	if (argc < 2) {
		std::cout << "Error: Not enough arguments!" << std::endl;
		return 1;
	}

	if (argc == 2 && pmergeme.checkOneArg(argv[1]))
		return 0;	
	
	int errPos = pmergeme.fillContainers(argc, argv);
	if (errPos != TRUE) {
		pmergeme.printErrPos(errPos);
		return 1;
	}

	pmergeme.copyContainers();
			
	gettimeofday(&tv, NULL);
	pmergeme.setEnd(tv, PARSE);

	gettimeofday(&tv, NULL);
	pmergeme.setStart(tv, VEC);

	pmergeme.fordJohnsonSortVector(pmergeme.getVector(OUT), 0, pmergeme.getVectorSize());
	
	gettimeofday(&tv, NULL);
	pmergeme.setEnd(tv, VEC);

	gettimeofday(&tv, NULL);
	pmergeme.setStart(tv, DEQ);

	pmergeme.fordJohnsonSortDeque(pmergeme.getDeque(OUT), 0, pmergeme.getDequeSize());
	
	gettimeofday(&tv, NULL);
	pmergeme.setEnd(tv, DEQ);

	if (pmergeme.areNumbersRepetitive(pmergeme.getVector(OUT))) {
		std::cout << "Error: Repetitive numbers found!" << std::endl;
		return 1;
	}

	pmergeme.printBefore();
	pmergeme.printAfter();
	pmergeme.printTimes();
}
