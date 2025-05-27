# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/07 20:11:55 by jkovacev          #+#    #+#              #
#    Updated: 2025/05/26 14:01:49 by jkovacev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror

SRCS = pipex.c \
		ft_split.c \
		ft_substr.c \
		parse_cmd.c \
		parse_envp.c \
		str_manipulation.c \
		free.c		

OBJDIR = objects
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

DEPS = pipex.h \
		str_manipulation.h

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: %.c $(DEPS)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re