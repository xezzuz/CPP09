# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/05 15:30:55 by nazouz            #+#    #+#              #
#    Updated: 2024/09/05 15:31:09 by nazouz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=			RPN

CPP				=			c++

CPPFLAGS		=			-Wall -Wextra -Werror

INCLUDES		=			RPN.hpp

SRCS			=			main.cpp RPN.cpp

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