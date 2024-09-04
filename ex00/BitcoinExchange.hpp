/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:06:54 by nazouz            #+#    #+#             */
/*   Updated: 2024/09/04 19:21:27 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>

class BitcoinExchange {
	private:
		std::ifstream						inputFile;
		std::ifstream						dataFile;

		std::map<std::string, double>		dataBase;
	
		void								storeDataBase();
		void								printDataBaseMap();

	public:
		BitcoinExchange(std::string inputName, std::string dataName);
		BitcoinExchange(const BitcoinExchange& original);
		BitcoinExchange& operator=(const BitcoinExchange& original);
		~BitcoinExchange();

		void			processInput();
		void			printResult(const std::string& date, const double& value);
		
};

#endif