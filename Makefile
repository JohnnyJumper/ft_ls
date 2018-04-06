# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtahirov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/03 17:27:11 by jtahirov          #+#    #+#              #
#    Updated: 2018/03/13 01:03:11 by jtahirov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I $(IDIR) -O3
NAME = ft_ls
IDIR = ./include

_DEPS = ft_ls.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

SRC = ft_ls.c ft_lsget.c uttility.c ft_lsparse.c ft_lssort.c ft_lssort_func.c \
	  ft_lstrain.c ft_lshandle.c ft_lssort_revfunc.c ft_lsget_func.c \
	  ft_lstrain_func.c
SRC_OBJ =$(SRC:.c=.o)

OBJ = $(SRC_OBJ)
LIBS = ./libft/libft.a

all: libftcreate $(NAME)

%.o: %.c $(DEPS)
	@echo "\033[0;32m\c"
	$(CC) -c -o $@ $< $(CFLAGS)
	@echo "\033[0m\c"

$(NAME): $(OBJ) $(LIBS)
	@echo "\033[0;36m\c"
	$(CC) -o $@ $^ $(LIBS) $(CFLAGS)
	@echo "\033[0m\c"

libftcreate:
	@+$(MAKE) -C ./libft

libftclean:
	@+$(MAKE) clean -C ./libft

libftfclean:
	@+$(MAKE) fclean -C ./libft

clean: libftclean
	@/bin/rm -f $(OBJ)

fclean: clean libftfclean
	@/bin/rm -f $(NAME)

re: fclean all libftclean libftfclean

.PHONY: clean fclean re
