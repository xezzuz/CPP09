/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:32:08 by nazouz            #+#    #+#             */
/*   Updated: 2024/09/11 13:27:17 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

bool			isValidToken(const std::string& token) {
	size_t			i = 0;

	if (token.empty())
		return false;
	for (; token[i] == ' '; i++)
		;
	for (; token[i]; i++)
		if (!isdigit(token[i]))
			break ;
	if (!token[i])
		return true;
	for (; token[i] == ' '; i++)
		;
	if (!token[i])
		return true;
	return false;
}
