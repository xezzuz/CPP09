/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:10:50 by nazouz            #+#    #+#             */
/*   Updated: 2024/09/07 17:11:13 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>

class PmergeMe {
	private:
		std::string				input;
		std::deque<int>			unsortedDeque;
		std::vector<int>		unsortedVector;
		std::deque<int>			sortedDeque;
		std::vector<int>		sortedVector;
		std::vector<int>		jacobNums;


		void					generateJacobNums(size_t size);
		void					parseSequence();
		bool					isValidSequence();
		void					mergeSort(std::vector< std::pair <int, int> >& sortedPairs);
		void					merge(std::vector< std::pair <int, int> >& sortedPairs,
										std::vector< std::pair <int, int> >& left,
											std::vector< std::pair <int, int> >& right);
		void					mainChainPend(std::vector< std::pair <int, int> >& sortedPairs, std::vector<int>& pendVector);
		void					insertPendToMainChain(std::vector<int>& pendChain);

		void					printElements();

	public:
		PmergeMe(const std::string& input);
		PmergeMe(const PmergeMe& original);
		PmergeMe& operator=(const PmergeMe& original);
		~PmergeMe();

		void					PmergeDeque();
		void					PmergeVector();
};

#endif