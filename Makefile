# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/25 12:00:15 by sgoffaux          #+#    #+#              #
#    Updated: 2021/09/10 10:40:32 by sgoffaux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CC		=	gcc
INCLUDE	=	includes
CFLAGS	=	-Wall -Wextra -Werror -I$(INCLUDE)
RM		=	rm -f
LIBFT = ./libft/libft.a
LIBFTDIR = ./libft

SRCS	=	main.c\
			utilities.c \

OBJ	=	$(SRCS:%.c=%.o)

all:		$(NAME)

$(NAME):	$(OBJ)
			$(MAKE) -C $(LIBFTDIR)
			@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
			

.c.o:
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
			$(MAKE) clean -C ./libft
			@$(RM) $(OBJ)
			
fclean:		clean
			$(MAKE) clean -C ./libft
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
