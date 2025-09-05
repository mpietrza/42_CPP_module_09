/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:38:10 by mpietrza          #+#    #+#             */
/*   Updated: 2025/09/05 17:21:21 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>

class PmergeMe
{
	private:
		std::vector<int> inputVector;
		std::deque<int> inputDeque;

		PmergeMe(const PmergeMe &other);	
		PmergeMe &operator=(const PmergeMe &other);
	
	public:
		PmergeMe();
		~PmergeMe();

		void fillContainers(int argc, char **argv);
		void fordJohnsonSortVector();
		void fordJohnsonSortDeque();

		void printBefore() const;
		void printAfterVector() const;
		void printAfterDeque() const;				
};

#endif