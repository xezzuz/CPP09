/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:54:57 by nazouz            #+#    #+#             */
/*   Updated: 2024/09/11 12:48:04 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(const std::string& argument) {
	notation = argument;

	parseNotation();
}

RPN::RPN(const RPN& original) {
	stack = original.stack;
	notation = original.notation;
	result = original.result;
}

RPN& RPN::operator=(const RPN& original) {
	if (this != &original) {
		stack = original.stack;
		notation = original.notation;
		result = original.result;
	}
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
	double	first;
	double	second;
	
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
		if (isdigit(token[0]) && token.length() != 1)
			throw "Error";
		// else if (token[0] == '-' && token.length() != 2)
		// 	throw "Error";
		if ((isdigit(token[0]) && token.length() == 1)
			|| (token[0] == '-' && isdigit(token[1]) && token.length() == 2))
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
