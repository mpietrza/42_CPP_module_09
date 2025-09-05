/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:45:56 by mpietrza          #+#    #+#             */
/*   Updated: 2025/09/05 17:21:09 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <cstdlib>

class RPN {
	private:
		RPN(const RPN &other);
		RPN &operator=(const RPN &other);

	public:
		RPN();
		~RPN();

		void evaluate(const std::string &input);
};

#endif