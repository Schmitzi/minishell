#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/06 15:51:12 by mgeiger-          #+#    #+#              #
#    Updated: 2024/05/17 14:04:25 by mgeiger-         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME 	= 	libft.a

CC 		= 	cc
CFLAGS	= 	-Wall -Wextra -Werror -g
AR		= 	ar -rcs
RM 		= 	rm -f

RED		=	\e[0;91m
BLUE	=	\e[0;94m
GREEN	=	\e[0;92m
YELLOW	=	\e[0;33m
WHITE	=	\e[0;97m
BOLD	=	\e[1m
U_LINE	=	\e[4m
RESET	=	\e[0m

FILES 	=	ft_atoi \
			ft_bzero \
			ft_calloc \
			ft_isalnum \
			ft_isalpha \
			ft_isascii \
			ft_isdigit \
			ft_isprint \
			ft_itoa \
			ft_memchr \
			ft_memcmp \
			ft_memcpy \
			ft_memmove \
			ft_memset \
			ft_putchar_fd \
			ft_putendl_fd \
			ft_putnbr_fd \
			ft_putstr_fd \
			ft_split \
			ft_strchr \
			ft_strcmp \
			ft_strcpy \
			ft_strdup \
			ft_striteri \
			ft_strjoin \
			ft_strlcat \
			ft_strlcpy \
			ft_strlen \
			ft_strmapi \
			ft_strncmp \
			ft_strnstr \
			ft_strrchr \
			ft_strtrim \
			ft_substr \
			ft_tolower \
			ft_toupper \
			ft_lstadd_back \
			ft_lstadd_front \
			ft_lstclear \
			ft_lstdelone \
			ft_lstiter \
			ft_lstlast \
			ft_lstmap \
			ft_lstnew \
			ft_lstsize \

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = obj/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

all: $(NAME)

$(OBJS_DIR)%.o: %.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) $@ $^

clean:
	$(RM) $(OBJS)
	if [ -d "$(OBJS_DIR)" ]; then \
		rm -r $(OBJS_DIR); \
	fi

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: bonus all clean fclean re
