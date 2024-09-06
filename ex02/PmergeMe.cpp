/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:17:06 by nazouz            #+#    #+#             */
/*   Updated: 2024/09/06 19:50:59 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(const std::string& input) {
	this->input = input;

	parseSequence();
}

PmergeMe::PmergeMe(const PmergeMe& original) {
	(void)original;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& original) {
	(void)original;
	return *this;
}

PmergeMe::~PmergeMe() {

}

bool			PmergeMe::isValidSequence() {
	for (int i = 0; input[i]; i++) {
		if (!isdigit(input[i]) && input[i] != ' ' && input[i] != '+')
			return false;
	}
	return true;
}

bool			isValidToken(const std::string& token) {
	size_t			i = 0;
	if (token[i] == '+' && !isdigit(token[++i]))
		return false;

	for (; token[i]; i++) {
		if (!isdigit(token[i]))
			return false;
	}
	return true;
}

void			PmergeMe::parseSequence() {
	if (isValidSequence()) {
		int				i = 0;
		int				toPush;
		std::string		token;
		
		while (input[i]) {
			token = "";
			while (input[i] && input[i] == ' ')
				i++;
			while (input[i] && input[i] != ' ')
				token += input[i++];
			if (!isValidToken(token) || token == "")
				throw "Error: Invalid Sequence";
			try {
				toPush = std::stoi(token);
			} catch (...) {
				throw "Error: Invalid Sequence";
			}
			unsortedDeque.push_back(toPush);
			unsortedVector.push_back(toPush);
		}
		printElements();
	}
	else
		throw "Error: Invalid Sequence";
}

void			PmergeMe::printElements() {
	printf("Vector: ");
	for (size_t i = 0; i < unsortedVector.size(); i++) {
		printf("[%d]", unsortedVector[i]);
	}
	printf("\n");
	
	printf("Deque: ");
	for (size_t i = 0; i < unsortedDeque.size(); i++) {
		printf("[%d]", unsortedDeque[i]);
	}
	printf("\n");
}

void					PmergeMe::PmergeDeque() {
	
}

void					PmergeMe::PmergeVector() {
	std::vector< std::pair<int, int> >		sortedPairs;

	for (size_t i = 0; i < unsortedVector.size(); i += 2) {
		std::pair<int, int>		pair;
		if (unsortedVector[i] < unsortedVector[i + 1]) {
			pair.first = unsortedVector[i + 1];
			pair.second = unsortedVector[i];
		}
		else {
			pair.first = unsortedVector[i];
			pair.second = unsortedVector[i + 1];
		}
		sortedPairs.push_back(pair);
	}
	printf("\n\nSorted Vector Pairs: ");
	for (size_t i = 0; i < sortedPairs.size(); i++) {
		printf("[%d][%d] | ", sortedPairs[i].first, sortedPairs[i].second);
	}
	printf("\n");
}
