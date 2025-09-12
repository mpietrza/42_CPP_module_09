/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:22:09 by mpietrza          #+#    #+#             */
/*   Updated: 2025/09/12 15:25:50 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sstream> //for std::istringstream
#include <algorithm> //for std::lower_bound
#include <deque> //for std::deque
#include <iomanip> //for std::setprecision

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

int PmergeMe::fillContainers(int argc, char **argv){
	if (argc < 2)
		return FALSE;
	
	if (argc == 2) {
		//data given as a single string argument or just one number
		// USE "shuf -i 1-100000 -n 3000 | xargs ./PmergeMe "
		// or "./PmergeMe $(shuf -i 1-100000 -n 3000 | tr '\n' ' ')" to generate random numbers
		std::istringstream iss(argv[1]);
		std::string token;
		int i = 0;
		while (iss >> token) {
			std::istringstream numStream(token);
			int val;
			char extra;
			if (!(numStream >> val) || (numStream >> extra) || val <= 0){
				return i + 1; // return the position of the invalid argument (1-based index)
			}
			else {
				_inputVector.push_back(val);
				_inputDeque.push_back(val);
			}
			i++;
		}
	}
	else {
		for (int i = 1; i < argc; ++i) {
			std::istringstream iss(argv[i]);
			int val;
			char extra;
			if (!(iss >> val) || (iss >> extra) || val <= 0)
				return i;
			_inputVector.push_back(val);
			_inputDeque.push_back(val);
		}
	}
	return TRUE;
}

void PmergeMe::fordJohnsonSortVector(std::vector<int> &vec, int start, int end) {
	int len = end - start;
	if (len <= 1)
		return;
	
	std::vector<int> mainChain; //bigger numbers
	std::vector<int> pending; //smaller numbers
	int i = start;

	for (; i + 1 < end; i += 2) {
		if (vec[i] < vec[i + 1]) {
			mainChain.push_back(vec[i + 1]);
			pending.push_back(vec[i]);
		}
		else {
			mainChain.push_back(vec[i]);
			pending.push_back(vec[i + 1]);
		}
	}
	//the last number without pair (if exists) is pushed to the main chain
	if (i < end)
		mainChain.push_back(vec[i]);
	
	//recursively go through the main chain
	fordJohnsonSortVector(mainChain, 0, mainChain.size());
	
	//push back the lower numbers from the pending chain to the main chain
	for (size_t j = 0; j < pending.size(); ++j) {
		std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), pending[j]);
		mainChain.insert(pos, pending[j]);
	}
	
	//push all the sorted numbers back to the input chain
	for (int k = 0; k < len; ++k)
		vec[start + k] = mainChain[k];

}

void PmergeMe::fordJohnsonSortDeque(std::deque<int> &deq, int start, int end) {
	int len = end - start;
	if (len <= 1)
		return;

	std::deque<int> mainChain;
	std::deque<int> pending;
	int i = start;

	for (; i + 1 < end; i += 2) {
		if (deq[i] < deq[i + 1]) {
			mainChain.push_back(deq[i + 1]);
			pending.push_back(deq[i]);
		}
		else {
			mainChain.push_back(deq[i]);
			pending.push_back(deq[i + 1]);
		}
	}

	if (i < end)
		mainChain.push_back(deq[i]);
	
	fordJohnsonSortDeque(mainChain, 0, mainChain.size());
	
	for (size_t j = 0; j < pending.size(); ++j) {
		std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), pending[j]);
		mainChain.insert(pos, pending[j]);
	}

	for (int k = 0; k < len; ++k)
		deq[start + k] = mainChain[k];
}

void PmergeMe::printBefore() const {
	std::cout << "Before: ";
	size_t i = 1; // is 1 for the normal mathematical counting from 1
	for (std::deque<int>::const_iterator it = _inputDeque.begin(); it != _inputDeque.end(); ++it, ++i) {
		if (i == PRINT_LIMIT + 1) {
			std::cout << "[...]" << std::endl;
			break;
		}
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

static bool areContainersEqual(const std::vector<int> &vec, const std::deque<int> &deq) {
	if (vec.size() != deq.size())
		return false;
	return std::equal(vec.begin(), vec.end(), deq.begin());
}

void PmergeMe::printAfter() const {
	if (!areContainersEqual(_inputVector, _inputDeque)) {
		std::cout << "Error: Vector and deque differ!" << std::endl;
		std::cout << "Vector: ";
		for (size_t i = 0; i < _inputVector.size(); ++i)
			std::cout << _inputVector[i] << " ";
		std::cout << std::endl;
		std::cout << "Deque:  ";
		for (size_t i = 0; i < _inputDeque.size(); ++i)
			std::cout << _inputDeque[i] << " ";
		std::cout << std::endl;
		return;
	}
	std::cout << "After:  ";
	size_t i = 1;
	for (std::vector<int>::const_iterator it = _inputVector.begin(); it != _inputVector.end(); ++it, ++i) {
		if (i == PRINT_LIMIT + 1) {
			std::cout << "[...]" << std::endl;
			break;
		}
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}


static double elapsedUSec(const struct timeval& start, const struct timeval& end) {
	return (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_usec - start.tv_usec);
}

void PmergeMe::printTimes() const {
	double vecTime = elapsedUSec(_startVector, _endVector); // microseconds
	double deqTime = elapsedUSec(_startDeque, _endDeque);   // microseconds

	std::cout << "Time to process the range of " << _inputVector.size()
			  << " elements with std::vector: "
			  << std::fixed << std::setprecision(0) << vecTime << " microseconds." << std::endl;

	std::cout << "Time to process the range of " << _inputDeque.size()
			  << " elements with std::deque: "
			  << std::fixed << std::setprecision(0) << deqTime << " microseconds." << std::endl;
}

std::vector<int> &PmergeMe::getVector() {
	return _inputVector;
}

std::deque<int> &PmergeMe::getDeque() {
	return _inputDeque;
}

int PmergeMe::getVectorSize() const {
	return _inputVector.size();
}

int PmergeMe::getDequeSize() const {
	return _inputDeque.size();
}


void PmergeMe::setStartVector(const timeval& tv) {
	_startVector = tv;
}

void PmergeMe::setEndVector(const timeval& tv) {
	_endVector = tv;
}

void PmergeMe::setStartDeque(const timeval& tv) {
	_startDeque = tv;
}

void PmergeMe::setEndDeque(const timeval& tv) {
	_endDeque = tv;
}
