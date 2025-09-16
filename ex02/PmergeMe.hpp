/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:38:10 by mpietrza          #+#    #+#             */
/*   Updated: 2025/09/16 14:33:52 by mpietrza         ###   ########.fr       */
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
#define TRUE  -2

#define PARSE 0
#define VEC   1
#define DEQ   2

#define IN  0
#define OUT 1

class PmergeMe
{
	private:
		std::vector<int> _inputVector;
		std::vector<int> _outputVector;
		std::deque<int> _inputDeque;
		std::deque<int> _outputDeque;
		struct timeval _startParsing; 
		struct timeval _endParsing;
		struct timeval _startVector; 
		struct timeval _endVector;
		struct timeval _startDeque;
		struct timeval _endDeque;

		PmergeMe(const PmergeMe &other);	
		PmergeMe &operator=(const PmergeMe &other);
	
	public:
		PmergeMe();
		~PmergeMe();
		
		bool checkOneArg(const char *arg);
		int fillContainers(int argc, char **argv);
		void fordJohnsonSortVector(std::vector<int> &vec, int start, int end);
		void fordJohnsonSortDeque(std::deque<int> &deq, int start, int end);

		void printBefore() const;
		void printAfter() const;
		void printTimes() const;
		int  printErrPos(const int errPos) const;

		void copyContainers();
		std::vector<int> &getVector(int mode);
		std::deque<int> &getDeque(int mode);
		int  getVectorSize() const;
		int  getDequeSize() const;

		bool areNumbersRepetitive(const std::vector<int> &vec) const;
		
		void setStart(const timeval& tv, const int mode);
		void setEnd(const timeval& tv, const int mode);

};

#endif
