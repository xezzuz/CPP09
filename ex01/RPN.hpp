/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:31:50 by nazouz            #+#    #+#             */
/*   Updated: 2024/09/05 18:14:06 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <algorithm>

class RPN {
	private:
		std::stack<int>		stack;
		std::string			notation;
		int					result;

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