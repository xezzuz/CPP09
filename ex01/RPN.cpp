/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:54:57 by nazouz            #+#    #+#             */
/*   Updated: 2024/09/05 19:16:19 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(const std::string& argument) {
	notation = argument;

	parseNotation();
}

RPN::RPN(const RPN& original) {
	(void)original;
}

RPN& RPN::operator=(const RPN& original) {
	(void)original;
	return *this;
}

RPN::~RPN() {

}

bool			RPN::isValidNotation() {
	for (int i = 0; notation[i]; i++) {
		if (notation[i] != ' ' && !isdigit(notation[i])
			&& notation[i] != '/' && notation[i] != '-'
			&& notation[i] != '+' && notation[i] != '*')
			return false;
	}
	return true;
}

void			RPN::parseNotation() {
	if (isValidNotation())
		calculateResult();
	else
		throw "Error";
}

void			RPN::calculateOperation(char op) {
	int		first;
	int		second;
	
	if (stack.size() < 2)
		throw "Error";
	second = stack.top();
	stack.pop();
	first = stack.top();
	stack.pop();
	if (op == '+')
		result = first + second;
	else if (op == '-')
		result = first - second;
	else if (op == '*')
		result = first * second;
	else if (op == '/' && second)
		result = first / second;
	else
		throw "Error";
	stack.push(result);
}

void			RPN::calculateResult() {
	int				i = 0;
	std::string		token;

	while (notation[i]) {
		token = "";
		while (notation[i] && notation[i] == ' ')
			i++;
		while (notation[i] && notation[i] != ' ')
			token += notation[i++];
		if (token.length() != 1)
			throw "Error";
		if (isdigit(token[0]))
			stack.push(std::stoi(token));
		else if (token == "+" || token == "-" || token == "*" || token == "/")
			calculateOperation(token[0]);
		else if (token != "")
			throw "Error";
	}
	if (stack.size() != 1)
		throw "Error";
	result = stack.top();	
}

void			RPN::printResult() {
	std::cout << result << std::endl;
}
