/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:17:06 by nazouz            #+#    #+#             */
/*   Updated: 2024/09/07 19:56:51 by nazouz           ###   ########.fr       */
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
		// printElements();
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

void			PmergeMe::generateJacobNums(size_t size) {
	int				j = 1;
	jacobNums.push_back(0);
	jacobNums.push_back(1);
	for (size_t i = 0; i <= size; i++) {
		jacobNums.push_back(jacobNums[j] + 2 * jacobNums[j - 1]);
		j++;
	}
}

void			PmergeMe::mainChainPend(std::vector< std::pair <int, int> >& sortedPairs, std::vector<int>& pendVector) {
	for (size_t i = 0; i < sortedPairs.size(); i++) {
		sortedVector.push_back(sortedPairs[i].first);
		pendVector.push_back(sortedPairs[i].second);
	}
}

void			PmergeMe::merge(	std::vector< std::pair <int, int> >& sortedPairs,
								std::vector< std::pair <int, int> >& left,
								std::vector< std::pair <int, int> >& right) {
	// printf("\n[Merge()]\n");
	// printf("\nVector : ");
	// for (size_t i = 0; i < sortedPairs.size(); i++) {
	// 	printf("[%d]", sortedPairs[i].first);
	// }
	// printf("\n");

	// printf("\nLeft : ");
	// for (size_t i = 0; i < left.size(); i++) {
	// 	printf("[%d]", left[i].first);
	// }
	// printf("\n");

	// printf("\nRight : ");
	// for (size_t i = 0; i < right.size(); i++) {
	// 	printf("[%d]", right[i].first);
	// }
	// printf("\n");
	size_t		i = 0, j = 0, k = 0;

	while (i < left.size() && j < right.size()) {
		if (left[i].first <= right[j].first) {
			sortedPairs[k] = left[i];
			i++;
		}
		else {
			sortedPairs[k] = right[j];
			j++;
		}
		k++;
	}

	while (i < left.size()) {
		sortedPairs[k] = left[i];
		i++;
		k++;
	}
	
	while (j < right.size()) {
		sortedPairs[k] = right[j];
		j++;
		k++;
	}
}

void					PmergeMe::mergeSort(std::vector< std::pair <int, int> >& sortedPairs) {
	int			mid;

	// base case
	if (sortedPairs.size() <= 1)
		return ;

	mid = sortedPairs.size() / 2;
	std::vector< std::pair <int, int> >	left(sortedPairs.begin(), sortedPairs.begin() + mid);
	std::vector< std::pair <int, int> >	right(sortedPairs.begin() + mid, sortedPairs.end());

	// printf("\n[MergeLeft]\n");
	mergeSort(left); // left side
	// printf("\n[MergeRight]\n");
	mergeSort(right); // right side
	// printf("\n[Merge()]\n");
	merge(sortedPairs, left, right);
	for (size_t i = 0; i < sortedPairs.size(); i++) {
		printf("[%d,%d]", sortedPairs[i].first, sortedPairs[i].second);
	}
	printf("\n");
}

void					PmergeMe::insertPendToMainChain(std::vector<int>& pendChain) {
	size_t							i;
	int								lastJn;
	int								currentJn;
	std::vector<int>::iterator		insertIt;
	size_t							insertedCount = 1;

	sortedVector.insert(sortedVector.begin(), pendChain[0]);
	
	i = 3;
	while (i < jacobNums.size() && insertedCount < pendChain.size()) {
		currentJn = jacobNums[i];
		lastJn = jacobNums[i - 1];

		while (currentJn > lastJn && insertedCount < pendChain.size()) {
			if (static_cast<size_t>(currentJn) >= pendChain.size())
				currentJn = pendChain.size();
			// printf("jacob number = [%d]\n", currentJn);
			// printf("number to insert = [%d]\n", pendChain[currentJn - 1]);
			insertIt = std::lower_bound(sortedVector.begin(), sortedVector.end(), pendChain[currentJn - 1]);
			// printf("number will be inserted in before: [%d]\n", *insertIt);
			sortedVector.insert(insertIt, pendChain[currentJn - 1]);
			insertedCount++;
			currentJn--;
			// printf("inserted count = [%lu] vs pend size = [%lu]\n", insertedCount, pendChain.size());
			// printf("------------------------------------------------------------------------\n");
		}
		i++;
	}
}

void					PmergeMe::PmergeDeque() {
	
}

void					PmergeMe::PmergeVector() {
	std::vector<int>						pendVector;
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
		printf("[%d,%d] ", sortedPairs[i].first, sortedPairs[i].second);
	}
	printf("\n\n");

	mergeSort(sortedPairs);
	mainChainPend(sortedPairs, pendVector);
	
	generateJacobNums(pendVector.size());

	printf("\nMainChain: ");
	for (size_t i = 0; i < sortedVector.size(); i++) {
		printf("[%d] ", sortedVector[i]);
	}
	printf("\n");

	printf("\nPendChain: ");
	for (size_t i = 0; i < pendVector.size(); i++) {
		printf("[%d] ", pendVector[i]);
	}
	printf("\n");
	
	printf("\nJacobSeq: ");
	for (size_t i = 0; i < jacobNums.size(); i++) {
		printf("[%d] ", jacobNums[i]);
	}
	printf("\n");

	insertPendToMainChain(pendVector);

	printf("\nFinalVector: ");
	for (size_t i = 0; i < sortedVector.size(); i++) {
		printf("[%d] ", sortedVector[i]);
	}
	printf("\n");
}
