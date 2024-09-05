/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:49:54 by nazouz            #+#    #+#             */
/*   Updated: 2024/09/05 18:15:35 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Error" << std::endl;
		return 1;
	}

	try {
		RPN			rpn(argv[1]);

		rpn.printResult();
	}
	catch (const char* s) {
		std::cerr << s << std::endl;
	}


	return 0;
}
