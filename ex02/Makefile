# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/06 17:10:11 by nazouz            #+#    #+#              #
#    Updated: 2024/09/06 17:10:19 by nazouz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=			PmergeMe

CPP				=			c++

CPPFLAGS		=			-Wall -Wextra -Werror

INCLUDES		=			PmergeMe.hpp

SRCS			=			main.cpp PmergeMe.cpp

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