/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:10:28 by nazouz            #+#    #+#             */
/*   Updated: 2024/09/06 19:47:07 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Usage: <positive integer sequence>" << std::endl;
		return 1;
	}

	try {
		PmergeMe		p(argv[1]);

		p.PmergeVector();
		// p.PmergeDeque();
	} catch (const char* s) {
		std::cerr << s << std::endl;
	}
	return 0;
}
