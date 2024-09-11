/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:10:50 by nazouz            #+#    #+#             */
/*   Updated: 2024/09/11 15:45:06 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <ctime>

#define BEFORE		1
#define AFTER		2
#define BENCHMARK	3
#define VECTOR		"std::vector"
#define DEQUE		"std::deque"

bool			isValidToken(const std::string& token);

template <typename Container, typename pairsContainer>
class PmergeMe {
	private:
		int						rem;
		char					**input;
		int						inputSize;
		bool					isOdd;
		clock_t					start;
		clock_t					end;
		Container				jacobNums;
		Container				sortedContainer;
		Container				unsortedContainer;


		void					generateJacobNums(size_t size);
		void					mergeSort(pairsContainer& sortedPairs);
		void					merge(pairsContainer& sortedPairs,
										pairsContainer& left,
											pairsContainer& right);
		void					mainChainPend(pairsContainer& sortedPairs, Container& pendVector);
		void					insertPendToMainChain(Container& pendChain);


	public:
		PmergeMe(char **argv, int argc);
		PmergeMe(const PmergeMe& original);
		PmergeMe& operator=(const PmergeMe& original);
		~PmergeMe();

		void					Pmerge();
		void					parseSequence();
		void					printState(const int state, const std::string& container);
};

// template <typename Container, typename pairsContainer>
template <typename Container, typename pairsContainer>
PmergeMe<Container, pairsContainer>::PmergeMe(char **argv, int argc) {
	this->input = argv;
	this->inputSize = argc - 1;
	this->rem = -1;
	this->isOdd = false;
}

template <typename Container, typename pairsContainer>
PmergeMe<Container, pairsContainer>::PmergeMe(const PmergeMe& original) {
	rem = original.rem;
	input = original.input;
	inputSize = original.inputSize;
	isOdd = original.isOdd;
	start = original.start;
	end = original.end;
	jacobNums = original.jacobNums;
	sortedContainer = original.sortedContainer;
	unsortedContainer = original.unsortedContainer;
}

template <typename Container, typename pairsContainer>
PmergeMe<Container, pairsContainer>& PmergeMe<Container, pairsContainer>::operator=(const PmergeMe<Container, pairsContainer>& original) {
	if (this != &original) {
		rem = original.rem;
		input = original.input;
		inputSize = original.inputSize;
		isOdd = original.isOdd;
		start = original.start;
		end = original.end;
		jacobNums = original.jacobNums;
		sortedContainer = original.sortedContainer;
		unsortedContainer = original.unsortedContainer;
	}
	return *this;
}

template <typename Container, typename pairsContainer>
PmergeMe<Container, pairsContainer>::~PmergeMe() {

}

template <typename Container, typename pairsContainer>
void			PmergeMe<Container, pairsContainer>::parseSequence() {
	int				i = 1;
	int				toPush;
	
	start = clock();
	while (input[i]) {
		if (!isValidToken(input[i]))
			throw "Error: Invalid Sequence";
		try {
			toPush = std::stoi(input[i]);
		} catch (...) {
			throw "Error: Invalid Sequence";
		}
		unsortedContainer.push_back(toPush);
		i++;
	}
}

template <typename Container, typename pairsContainer>
void			PmergeMe<Container, pairsContainer>::printState(const int state, const std::string& container) {
	if (state == BENCHMARK) {
		double d_elapsed = static_cast<double>(end - start) / CLOCKS_PER_SEC;
		std::cout << "Time to process a range of " << unsortedContainer.size() + isOdd;
		std::cout << " elements with " << container << " : " << d_elapsed * 1e6 << " µs" << std::endl;
	}
	else if (state == BEFORE) {
		std::cout << "Before: ";
		for (size_t i = 0; i < unsortedContainer.size(); i++) {
			std::cout << unsortedContainer[i] << " ";
		}
		std::cout << std::endl;
	} else if (state == AFTER) {
		std::cout << "After: ";
		for (size_t i = 0; i < sortedContainer.size(); i++) {
			std::cout << sortedContainer[i] << " ";
		}
		std::cout << std::endl;
	}
}

template <typename Container, typename pairsContainer>
void			PmergeMe<Container, pairsContainer>::generateJacobNums(size_t size) {
	if (jacobNums.size())
		return ;
	int				j = 1;
	jacobNums.push_back(0);
	jacobNums.push_back(1);
	for (size_t i = 0; i <= size; i++) {
		jacobNums.push_back(jacobNums[j] + 2 * jacobNums[j - 1]);
		j++;
	}
}

template <typename Container, typename pairsContainer>
void			PmergeMe<Container, pairsContainer>::mainChainPend(pairsContainer& sortedPairs, Container& pendContainer) {
	for (size_t i = 0; i < sortedPairs.size(); i++) {
		sortedContainer.push_back(sortedPairs[i].first);
		pendContainer.push_back(sortedPairs[i].second);
	}
}

template <typename Container, typename pairsContainer>
void			PmergeMe<Container, pairsContainer>::merge(	pairsContainer& sortedPairs,
								pairsContainer& left,
								pairsContainer& right) {
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

template <typename Container, typename pairsContainer>
void					PmergeMe<Container, pairsContainer>::mergeSort(pairsContainer& sortedPairs) {
	int			mid;

	if (sortedPairs.size() <= 1)
		return ;

	mid = sortedPairs.size() / 2;
	pairsContainer	left(sortedPairs.begin(), sortedPairs.begin() + mid);
	pairsContainer	right(sortedPairs.begin() + mid, sortedPairs.end());

	mergeSort(left);
	mergeSort(right);
	merge(sortedPairs, left, right);
}

template <typename Container, typename pairsContainer>
void					PmergeMe<Container, pairsContainer>::insertPendToMainChain(Container& pendChain) {
	size_t							i;
	int								lastJn;
	int								currentJn;
	typedef typename Container::iterator				iterator;
	iterator						insertIt;
	size_t							insertedCount = 1;

	sortedContainer.insert(sortedContainer.begin(), pendChain[0]);
	
	i = 3;
	while (i < jacobNums.size() && insertedCount < pendChain.size()) {
		currentJn = jacobNums[i];
		lastJn = jacobNums[i - 1];

		while (currentJn > lastJn && insertedCount < pendChain.size()) {
			if (static_cast<size_t>(currentJn) >= pendChain.size())
				currentJn = pendChain.size();
			insertIt = std::lower_bound(sortedContainer.begin(), sortedContainer.end(), pendChain[currentJn - 1]);
			sortedContainer.insert(insertIt, pendChain[currentJn - 1]);
			insertedCount++;
			currentJn--;
		}
		i++;
	}
	if (rem != -1) {
		insertIt = std::lower_bound(sortedContainer.begin(), sortedContainer.end(), rem);
		sortedContainer.insert(insertIt, rem);
	}
}

template <typename Container, typename pairsContainer>
void					PmergeMe<Container, pairsContainer>::Pmerge() {
	Container								pendContainer;
	pairsContainer							sortedPairs;

	if (unsortedContainer.size() == 1) {
		sortedContainer.push_back(unsortedContainer[0]);
		return ;
	}
	isOdd = unsortedContainer.size() % 2;
	if (isOdd) {
		rem = unsortedContainer.back();
		unsortedContainer.pop_back();
	}
	for (size_t i = 0; i < unsortedContainer.size(); i += 2) {
		std::pair<int, int>		pair;
		if (unsortedContainer[i] < unsortedContainer[i + 1]) {
			pair.first = unsortedContainer[i + 1];
			pair.second = unsortedContainer[i];
		}
		else {
			pair.first = unsortedContainer[i];
			pair.second = unsortedContainer[i + 1];
		}
		sortedPairs.push_back(pair);
	}
	
	mergeSort(sortedPairs);
	mainChainPend(sortedPairs, pendContainer);
	generateJacobNums(pendContainer.size());
	insertPendToMainChain(pendContainer);
	end = clock();
}

#endif