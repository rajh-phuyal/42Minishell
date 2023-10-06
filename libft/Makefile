# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/02 16:15:26 by rphuyal           #+#    #+#              #
#    Updated: 2023/07/25 22:00:24 by rphuyal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = @cc

CFLAGS = -Wall -Wextra -Werror -I .

RM = rm -f

# COLORS
CBOLD   = \033[0;1m
RED     = \033[0;41m
GREEN   = \033[0;42m
BLUE   = \033[0;44m
YELLOW  = \033[0;43m
RESET   = \033[0m

SRC    = strings/ft_atoi.c \
		memory/ft_bzero.c \
		chars/ft_isalnum.c \
		chars/ft_isalpha.c \
		chars/ft_isascii.c \
		chars/ft_isdigit.c\
		chars/ft_isprint.c \
		memory/ft_memchr.c \
		memory/ft_memcmp.c \
		strings/ft_striteri.c \
		strings/ft_split.c \
		memory/ft_memcpy.c \
		memory/ft_memmove.c \
		memory/ft_memset.c \
		fd_insert/ft_putendl_fd.c \
		fd_insert/ft_putchar_fd.c \
		fd_insert/ft_putstr_fd.c \
		fd_insert/ft_putnbr_fd.c\
		strings/ft_strchr.c \
		strings/ft_strlcpy.c \
		strings/ft_strmapi.c\
		strings/ft_strdup.c \
		strings/ft_split.c \
		memory/ft_calloc.c \
		strings/ft_itoa.c \
		strings/ft_strlen.c \
		strings/ft_splitlen.c \
		strings/ft_emptystr.c \
		strings/ft_strncmp.c \
		strings/ft_substr.c \
		strings/ft_strtrim.c \
		strings/ft_strnstr.c \
		strings/ft_strrchr.c \
		strings/ft_strjoin.c \
		chars/ft_tolower.c \
		chars/ft_toupper.c \
		strings/ft_strlcat.c \
		printf/ft_printf.c \
		printf/extras.c \
		printf/getstrs.c \
		t_list/ft_lstnew.c\
		t_list/ft_lstadd_front.c \
		t_list/ft_lstsize.c \
		t_list/ft_lstlast.c \
		t_list/ft_lstadd_back.c \
		t_list/ft_lstdelone.c \
		t_list/ft_lstclear.c \
		t_list/ft_lstiter.c \
		t_list/ft_lstmap.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \

OBJ = $(SRC:.c=.o)

all:	$(NAME)

$(NAME):    $(OBJ)
	@ar rcs $(NAME) $(OBJ)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re:	fclean $(NAME)
