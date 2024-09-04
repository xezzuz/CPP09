# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 12:11:35 by nazouz            #+#    #+#              #
#    Updated: 2024/09/04 12:11:53 by nazouz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=			btc

CPP				=			c++

CPPFLAGS		=			-Wall -Wextra -Werror

INCLUDES		=			BitcoinExchange.hpp

SRCS			=			main.cpp BitcoinExchange.cpp

OBJS			=			$(SRCS:.cpp=.o)

all : $(NAME)

%.o : %.cpp $(INCLUDES)
	$(CPP) -c $(CPPFLAGS) $< -o $@

$(NAME) : $(OBJS)
	$(CPP) $(OBJS) -o $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all