/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:33:31 by nazouz            #+#    #+#             */
/*   Updated: 2024/09/04 19:26:31 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string inputName, std::string dataName) {
	dataFile.open(dataName, std::ios_base::in);
	if (!dataFile.is_open())
		throw "Error: could not open file.";
	inputFile.open(inputName, std::ios_base::in);
	if (!inputFile.is_open())
		throw "Error: could not open file.";
	storeDataBase();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& original) {
	(void)original;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& original) {
	(void)original;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {

}

void			BitcoinExchange::printDataBaseMap() {
	std::cout << "DataBase Map Content: " << std::endl;
	std::map<std::string, double>::iterator it = dataBase.begin();
	for (; it != dataBase.end(); it++) {
		std::cout << it->first << " | " << it->second << std::endl;
	}
}

void			BitcoinExchange::storeDataBase() {
	std::string			line;
	std::string			date;
	double				value;

	while (!dataFile.eof()) {
		std::getline(dataFile, line);
		if (line.empty() || line == "date,exchange_rate")
			continue;
		// try catch
		date = line.substr(0, line.find(','));
		value = std::stod(line.substr(line.find(',') + 1));
		dataBase[date] = value;
	}
	// printDataBaseMap();
}

bool			isFormat(const std::string& line) {
	// shortest valid format
	if (line.length() < 14)
		return false;
	
	// YYYY-MM-DD
	for (int i = 0; i < 4; i++)
		if (!isdigit(line[i]))
			return false;
	if (line[4] != '-' || line[7] != '-')
		return false;
	for (int i = 5; i < 7; i++)
		if (!isdigit(line[i]))
			return false;
	for (int i = 8; i < 10; i++)
		if (!isdigit(line[i]))
			return false;
	
	// " | "
	if (line.substr(10, 3) != " | ")
		return false;
	// value
	int		i = 13;
	if (!isdigit(line[i]) && line[i] != '-')
		return false;
	return true;
}

bool			isValidInput(const std::string& date, const double& value) {
	(void)date;
	(void)value;
	return true;
}

void			BitcoinExchange::printResult(const std::string& date, const double& value) {
	if (isValidInput(date, value)) {
		std::map<std::string, double>::iterator	it = dataBase.find(date);
		if (it == dataBase.end())
			printf("youkahlif\n");
		printf("[%f]\n", it->second);
		std::cout << date << " => " << value << " * " << it->second << std::endl;
		// std::cout << date << " => " << value << " = " 
		// 		  << std::fixed << std::setprecision(1) << value * it->second << std::endl;
	}
}

void			BitcoinExchange::processInput() {
	std::string			line;
	std::string			date;
	double				value;

	std::getline(inputFile, line);
	if (line != "date | value")
		throw std::exception(); // don't accept input
	while (!inputFile.eof()) {
		std::getline(inputFile, line);
		// std::cout << "[" << line << "]" << std::endl;
		if (line.empty())
			throw std::exception(); // don't accept empty lines
		if (isFormat(line)) {
			date = line.substr(0, line.find('|') - 1);
			value = std::stod(line.substr(line.find('|') + 1));
			// std::cout << "[" << date << "]" << "[" << value << "] V" << std::endl;
			printResult(date, value);
		}
		else
			std::cout << "\n[" << line << "] NV\n" << std::endl;
	}
}
