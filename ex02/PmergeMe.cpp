/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:22:09 by mpietrza          #+#    #+#             */
/*   Updated: 2025/09/08 15:20:07 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

void PmergeMe::fillContainers(int argc, char **argv){
	
}

void PmergeMe::fordJohnsonSortVector(std::vector<int> &vec, int start, int end) {
	int len = end - start;
	if (len <= 1)
		return;
	
	std::vector<int> mainChain; //bigger numbers
	std::vector<int> pending; //smaller numbers

	for (int i = start; i + 1 < end; i += 2) {
		if (vec[i] < vec[i + 1]) {
			mainChain.push_back(vec[i + 1]);
			pending.push_back(vec[i]);
		}
		else {
			mainChain.push_back(vec[i]);
			pending.push_back(vec[i + 1];
		}
	}
	//the last number without pair (if exists) is pushed to the main chain
	if (i < end)
		mainChain.push_back(vec[i]);
	
	//recursively go through the main chain
	fordJohnsonSortVector(mainChain, 0, mainChain, 0, mainChain.size());

	for (size_t j = 0; k < pending.size(); ++j) {
		std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), pending[i]);
		mainChain.insert(pos, pending[j]);
	}

	for (int k = 0; k < n; ++k)
		vec[start + k] = mainChain[k];

}
