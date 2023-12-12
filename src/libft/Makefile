# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guortun- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/09 19:52:32 by guortun-          #+#    #+#              #
#    Updated: 2022/08/09 20:35:24 by guortun-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c\
	   ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c\
	   ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c\
	   ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c\
	   ft_atoi.c ft_calloc.c ft_strdup.c ft_memcpy.c\
	   ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_putchar_fd.c\
	   ft_putstr_fd.c ft_putnbr_fd.c ft_substr.c ft_strjoin.c\
	   ft_itoa.c ft_putendl_fd.c ft_strmapi.c ft_strtrim.c ft_split.c\
	   ft_striteri.c\

BONUS_FILES = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c\
				ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstmap_bonus.c\

OBJS = $(FILES:.c=.o)

OBJBONUS = $(BONUS_FILES:.c=.o)

Cflags = -Wall -Wextra -Werror

NAME = libft.a

LIB = libft.h


##################################################

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJS): $(FILES) $(LIB)
	gcc $(Cflags) -c $(FILES)

clean:
	rm  -f $(OBJS) $(OBJBONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(OBJBONUS) $(LIB)
	ar rc $(NAME) $(OBJBONUS)
	ranlib $(NAME)

$(OBJBONUS): $(BONUS_FILES) $(LIB)
	gcc $(Cflgas) -c $(BONUS_FILES)

.PHONY: all clean fclean re bonus
