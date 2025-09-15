/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:22:09 by mpietrza          #+#    #+#             */
/*   Updated: 2025/09/15 19:01:24 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sstream> //for std::istringstream
#include <algorithm> //for std::lower_bound
#include <deque> //for std::deque
#include <iomanip> //for std::setprecision

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

bool PmergeMe::checkOneArg(const char *arg) {
	int i = 0;
	bool oneArg = true;
	
	while (arg[i] == ' ')
		i++;
	if (arg[i] == '\0') {
		std::cout << "Error: only one argument: empty string, so there is nothing to sort!" << std::endl;
		return true;
	}
	while (arg[i]) {
		if (arg[i] == ' ' && arg[i + 1] && arg[i + 1] != ' ')
			oneArg = false;
		i++;
	}
	if (oneArg == true) {
		std::cout << "Error: only one argument: " << arg << ", so there is nothing to sort!" << std::endl;
	}
	return oneArg;
}

int PmergeMe::fillContainers(int argc, char **argv){
	if (argc < 2)
		return FALSE;
	
	if (argc == 2) {
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
	if (!areContainersEqual(_outputVector, _outputDeque)) {
		std::cout << "Error: Vector and deque differ!" << std::endl;
		std::cout << "Vector: ";
		for (size_t i = 0; i < _outputVector.size(); ++i)
			std::cout << _outputVector[i] << " ";
		std::cout << std::endl;
		std::cout << "Deque:  ";
		for (size_t i = 0; i < _outputDeque.size(); ++i)
			std::cout << _outputDeque[i] << " ";
		std::cout << std::endl;
		return;
	}
	std::cout << "-------------------------" << std::endl;
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
	return (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
}

void PmergeMe::printTimes() const {
	double parsingTime = elapsedUSec(_startParsing, _endParsing); // microseconds
	double vecTime = elapsedUSec(_startVector, _endVector) + parsingTime; // microseconds
	double deqTime = elapsedUSec(_startDeque, _endDeque) + parsingTime;   // microseconds

	std::cout << "Time to process the range of " << _inputVector.size()
			  << " elements with std::vector: "
			  << std::fixed << std::setprecision(1) << vecTime << " microseconds." << std::endl;

	std::cout << "Time to process the range of " << _inputDeque.size()
			  << " elements with std::deque: "
			  << std::fixed << std::setprecision(1) << deqTime << " microseconds." << std::endl;
}

int PmergeMe::printErrPos(const int errPos) const {
		std::cout << "Error in given arguments!" << std::endl;
		if (errPos != FALSE)
			std::cout  << "argument is on the position: " << errPos << std::endl;
		return 1;
}

void PmergeMe::copyContainers() {
	_outputVector = _inputVector;
	_outputDeque = _inputDeque;
}

std::vector<int> &PmergeMe::getVector(int mode) {
	if (mode == IN)
		return _inputVector;
	else if (mode == OUT)
		return _outputVector;
	else
		std::cout << "Error in getters" << std::endl;
	return _inputVector; //to avoid compiler warning
}

std::deque<int> &PmergeMe::getDeque(int mode) {
	if (mode == IN)
		return _inputDeque;
	else if (mode == OUT)
		return _outputDeque;
	else
		std::cout << "Error in getters" << std::endl;
	return _inputDeque; //to avoid compiler warning
}

int PmergeMe::getVectorSize() const {
	return _inputVector.size();
}

int PmergeMe::getDequeSize() const {
	return _inputDeque.size();
}

bool PmergeMe::areNumbersRepetitive(const std::vector<int> &vec) const {
	for (size_t i = 1; i < vec.size(); ++i) {
		if (vec[i] == vec[i - 1])
			return true;
	}
	return false;
}

void PmergeMe::setStart(const timeval& tv, const int mode) {
	if (mode == PARSE) 
		_startParsing = tv;
	else if (mode == VEC)
		_startVector = tv;
	else if (mode == DEQ)
		_startDeque = tv;
	else
		std::cout << "Error in time counting!" << std::endl;
}

void PmergeMe::setEnd(const timeval& tv, const int mode) {
	if (mode == PARSE)
		_endParsing = tv;
	else if (mode == VEC)
		_endVector = tv;
	else if (mode == DEQ)
		_endDeque = tv;
}
