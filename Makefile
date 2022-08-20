# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clora-ro <clora-ro@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 09:20:12 by clora-ro          #+#    #+#              #
#    Updated: 2022/08/19 13:03:29 by clora-ro         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME 		= philosophers

SRCS		=	error.c			\
				main.c			\
				init_philo.c	\
				init_thread.c	\
				utils.c

OBJS		= $(SRCS:.c=.o)

CC			= gcc

CFLAGS		= -Wall -Wextra

RM			= rm -f

CLEAN		= CLEAN

all			: libft $(NAME)

libft		:
			$(MAKE) -C libft

$(NAME)		: $(addprefix objs/, $(OBJS)) libft/libft.a
			$(CC) $(CFLAGS) -pthread -lpthread -o $(NAME) $^

objs/%.o	:	%.c includes/philosophers.h libft/libft.h Makefile
				@mkdir -p objs
				$(CC) $(CFLAGS) -I includes -c $< -o $@

			
clean		:
			rm -rf objs/
			make clean -C libft

fclean		: clean
			rm -f $(NAME)
			make fclean -C libft

re			: fclean all

.PHONY		: all clean re fclean libft