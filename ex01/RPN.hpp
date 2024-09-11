/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:31:50 by nazouz            #+#    #+#             */
/*   Updated: 2024/09/11 12:33:48 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <algorithm>

class RPN {
	private:
		std::stack<double>	stack;
		std::string			notation;
		double				result;

		void				parseNotation();
		bool				isValidNotation();
		void				calculateResult();
		void				calculateOperation(char op);

	public:
		RPN(const std::string& argument);
		RPN(const RPN& original);
		RPN& operator=(const RPN& original);
		~RPN();

		void				printResult();
};

#endif