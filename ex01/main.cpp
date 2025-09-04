/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:43:15 by mpietrza          #+#    #+#             */
/*   Updated: 2025/09/04 19:14:49 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "Error: wrong number of arguments given; use a string in \"\"!" << std::endl;
		return 1;
	}
 	RPN rpn;
	rpn.evaluate(argv[1]);
	return 0;
}
