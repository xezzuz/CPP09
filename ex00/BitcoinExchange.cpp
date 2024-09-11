/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:33:31 by nazouz            #+#    #+#             */
/*   Updated: 2024/09/11 15:27:21 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
	// private constructor
}

BitcoinExchange::BitcoinExchange(std::string inputName, std::string dataName) {
	dataFile.open(dataName, std::ios_base::in);
	if (!dataFile.is_open())
		throw "Error: could not open data base file.";
	inputFile.open(inputName, std::ios_base::in);
	if (!inputFile.is_open())
		throw "Error: could not open file.";
	storeDataBase();
	storeDatesBase();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& original) {
	dataBase = original.dataBase;
	datesBase = original.datesBase;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& original) {
	if (this != &original) {
		dataBase = original.dataBase;
		datesBase = original.datesBase;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {
	inputFile.close();
	dataFile.close();
}

void			BitcoinExchange::printDataBaseMap() {
	std::cout << "DataBase Map Content: " << std::endl;
	std::map<std::string, double>::iterator it = dataBase.begin();
	for (; it != dataBase.end(); it++) {
		std::cout << it->first << " | " << it->second << std::endl;
	}
}

bool			isLeapYear(int year) {
	if (year % 400 == 0)
		return true;
    else if (year % 100 == 0)
		return false;
    else if (year % 4 == 0)
		return true;
    return false;
}

void			BitcoinExchange::storeDataBase() {
	std::string			line;
	std::string			date;
	double				value;

	std::getline(dataFile, line);
	if (dataFile.eof() || line.empty() || line != "date,exchange_rate")
		throw "Database file is not valid.";
	while (!dataFile.eof()) {
		std::getline(dataFile, line);
		if (line.empty())
			continue;
		date = line.substr(0, line.find(','));
		try {
			value = std::stod(line.substr(line.find(',') + 1));
		} catch (const std::exception& e) {
			throw "Database file is not valid.";
		}
		dataBase[date] = value;
	}
	if (datesBase.empty())
		throw "Database file is not valid.";
}

void			BitcoinExchange::storeDatesBase() {
	datesBase["01"] = 31;
	datesBase["02"] = 28;
	datesBase["03"] = 31;
	datesBase["04"] = 30;
	datesBase["05"] = 31;
	datesBase["06"] = 30;
	datesBase["07"] = 31;
	datesBase["08"] = 31;
	datesBase["09"] = 30;
	datesBase["10"] = 31;
	datesBase["11"] = 30;
	datesBase["12"] = 31;
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
	
	++i;
	bool		isDouble = false;
	while (line[i]) {
		if (!isdigit(line[i]) && line[i] != '.')
			return false;
		else if (line[i] == '.') {
			isDouble = true;
			i++;
			break ;
		}
		i++;
	}
	while (line[i]) {
		if (!isdigit(line[i]) && isDouble)
			return false;
		i++;
	}
	return true;
}

bool			BitcoinExchange::isValidInput(const std::string& date, const double& value) {
	std::map<std::string, int>::iterator		it;
	size_t										dateFormat[3];

	// validate value
	if (value < 0) {
		std::cout << "Error: not a positive number." << std::endl;
		return false;
	} else if (value > 1000){
		std::cout << "Error: too large a number." << std::endl;
		return false;
	}

	// validate date
	dateFormat[0] = std::stoi(date);
	isLeapYear(dateFormat[0]) ? datesBase["02"] = 29 : datesBase["02"] = 28;
	dateFormat[1] = std::stoi(&date[5]);
	if (dateFormat[1] < 1 || dateFormat[1] > 12) {
		std::cout << "Error: bad input => " << date << std::endl;
		return false;
	}
	dateFormat[2] = std::stoi(&date[8]);
	it = datesBase.find(date.substr(5, 2));
	if (dateFormat[2] < 1 || static_cast<int>(dateFormat[2]) > it->second) {
		std::cout << "Error: bad input => " << date << std::endl;
		return false;
	}
	return true;
}

void			BitcoinExchange::printResult(const std::string& date, const double& value) {
	if (isValidInput(date, value)) {
		// lower_bound find key >= keyToFind
		std::map<std::string, double>::iterator	it = dataBase.lower_bound(date);

		if (it == dataBase.end())
			it--;
		else if (it != dataBase.begin() && it->first != date)
			it--;
		std::cout << date << " => " << value << " = " 
				  << value * it->second << std::endl;
	}
}

void			BitcoinExchange::processInput() {
	std::string			line;
	std::string			date;
	double				value;

	std::getline(inputFile, line);
	if (line != "date | value")
		throw "Error: input file doesn't match the requirements.";
	while (!inputFile.eof()) {
		std::getline(inputFile, line);
		if (line.empty())
			continue;
		if (isFormat(line)) {
			date = line.substr(0, line.find('|') - 1);
			try {
				value = std::stod(line.substr(line.find('|') + 1));
			} catch (const std::exception& e) {
				std::cout << "Error: bad input => " << line << std::endl;
				continue;
			}
			printResult(date, value);
		}
		else
			std::cout << "Error: bad input => " << line << std::endl;
	}
}
