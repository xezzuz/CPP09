/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:15:07 by nazouz            #+#    #+#             */
/*   Updated: 2024/09/11 12:00:53 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

	try {
		BitcoinExchange			btc(argv[1], "data.csv");
		btc.processInput();
	} catch (const char* s) {
		std::cerr << s << std::endl;
	} catch (std::exception& e) {
		std::cerr << "Error: Input error" << std::endl;
	}

	return 0;
}
