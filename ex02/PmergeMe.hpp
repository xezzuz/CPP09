/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:10:50 by nazouz            #+#    #+#             */
/*   Updated: 2024/09/06 19:33:22 by nazouz           ###   ########.fr       */
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

		void					parseSequence();
		bool					isValidSequence();

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