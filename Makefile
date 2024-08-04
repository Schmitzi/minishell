# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miturk <miturk@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/03 11:31:53 by mgeiger-          #+#    #+#              #
#    Updated: 2024/07/19 16:21:48 by miturk           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the program
NAME    =   minishell

# Compiler
CC      =   cc
CFLAGS  =   -Wall -Werror -Wextra -g -fPIE
READ    =   -lreadline
RM      =   rm -f
INC     =   libft/libft.a
MAKEFLAGS += --no-print-directory

# Colours
RED		=	\e[0;91m
YELLOW  =   \e[0;33m
GREEN   =   \e[0;92m
RESET   =   \e[0m

# Files
FILES   =   alias \
			builtins \
			cd_tools \
			cmd \
			decider \
			decide_sub \
			env \
			env_util \
			env_util2 \
			env_name \
            error \
            expand \
			expand_util \
            export \
			free \
			ft_cd \
            heredoc \
			heredoc_stack \
			heredoc_util \
            init \
			input \
			libft_plus \
            main \
            parsing \
			path \
            pipeing \
			piping_util \
            prompt \
			quotes \
			redir \
			redir_utils \
			redir_utils2 \
			signal_handler \
            signals \
			syntax \
			token \
			token_util \
            utils \
			utils2 \

# Directories
SRC_DIR =   ./
SRC     =   $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))

OBJ_DIR =   obj/
OBJ     =   $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

# Rules

all:    	libft $(NAME)

$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): 	$(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(READ) -o $(NAME) $(INC)

libft:
	@make -C libft/

clean:
	@echo "$(RED)Cleaning...$(RESET)";
	@$(RM) $(OBJ)
	@$(RM) -r $(OBJ_DIR)
	@make -C libft/ clean > /dev/null;

fclean: 	clean
	@$(RM) $(NAME)
	@$(RM) -r $(OBJ_DIR)
	@make -C libft/ fclean > /dev/null;

re: 		fclean $(OBJ)
	clear ;
	@if [ -n "$(shell $(CC) -MM $(SRC))" ]; then \
		echo "$(YELLOW)Recompiling...$(RESET)"; \
		make all > /dev/null; \
        echo "$(GREEN)Minishell is ready$(RESET)"; \
	fi

# Phony
.PHONY: all clean fclean re libft
