/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:10:30 by mpietrza          #+#    #+#             */
/*   Updated: 2025/09/04 19:17:55 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

void RPN::evaluate(const std::string &input) {
	std::istringstream iss(input);
	std::string token;
	std::stack<double> stack;
	
	while (iss >> token) {
		if (token == "+" || (token == "-" && token.length() == 1) || token == "*" || token == "/") {
			if (stack.size() < 2) {
				std::cout << "Error: not enough operands!" << std::endl;
				return;
			}
			double b = stack.top(); stack.pop();
			double a = stack.top(); stack.pop();
			double result = 0;
			if (token == "+") result = a + b;
			else if (token == "-") result = a - b;
			else if (token == "*") result = a * b;
			else if (token == "/") {
				if (b == 0) {
					std::cout << "Error: result of division by zero is always infinity!" << std::endl;
					return;
				}
				result = a / b;
			}
			stack.push(result);
		}
		else {
			if (token.length() != 1 /*|| !(token.lenght == 2 && token[0] == '-')*/) {
				std::cout << "Error: you can only use single digit numbers!" << std::endl;
				return ;
			}
			char *endptr;
			double number = strtod(token.c_str(), &endptr);
			if (*endptr != '\0' || number >= 10 /*|| number <= -10*/) {
				std::cout << "Error: invalid token: " << token << "!" << std::endl;
				return ;
			}
			stack.push(number);
		}
	}
	if (stack.size() == 1)
		std::cout << "Result is: " << stack.top() << std::endl;
	else
		std::cout << "Error: invalid RPN string given!" << std::endl;
}
