/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:10:28 by nazouz            #+#    #+#             */
/*   Updated: 2024/09/11 13:26:55 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << "Usage: <positive integer sequence>" << std::endl;
		return 1;
	}

	try {
		PmergeMe< std::vector<int>, std::vector< std::pair<int, int> > >		vector(argv, argc);

		vector.parseSequence();
		vector.printState(BEFORE, VECTOR);
		vector.Pmerge();
		vector.printState(AFTER, VECTOR);
		vector.printState(BENCHMARK, VECTOR);

		PmergeMe< std::deque<int>, std::deque< std::pair<int, int> > >			deque(argv, argc);

		deque.parseSequence();
		deque.Pmerge();
		deque.printState(BENCHMARK, DEQUE);
	} catch (const char* s) {
		std::cerr << s << std::endl;
	} catch (...) {
		std::cerr << "Error: Exception Caught" << std::endl;
	}
	return 0;
}
