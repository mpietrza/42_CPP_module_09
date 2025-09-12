/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosz <milosz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:38:10 by mpietrza          #+#    #+#             */
/*   Updated: 2025/09/12 11:31:04 by milosz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <sys/time.h> //for gettimeofday

#define PRINT_LIMIT 3000
#define FALSE -1
#define TRUE -2

class PmergeMe
{
	private:
		std::vector<int> _inputVector;
		std::deque<int> _inputDeque;
		struct timeval _startVector; 
		struct timeval _endVector;
		struct timeval _startDeque;
		struct timeval _endDeque;

		PmergeMe(const PmergeMe &other);	
		PmergeMe &operator=(const PmergeMe &other);
	
	public:
		PmergeMe();
		~PmergeMe();

		int fillContainers(int argc, char **argv);
		void fordJohnsonSortVector(std::vector<int> &vec, int start, int end);
		void fordJohnsonSortDeque(std::deque<int> &deq, int start, int end);

		void printBefore() const;
		void printAfter() const;
		void printTimes() const;

		std::vector<int> &getVector();
		std::deque<int> &getDeque();
		int  getVectorSize() const;
		int  getDequeSize() const;

		void setStartVector(const timeval& tv);
		void setEndVector(const timeval& tv);
		void setStartDeque(const timeval& tv);
		void setEndDeque(const timeval& tv);
};

#endif
