# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/20 10:25:55 by agiliber          #+#    #+#              #
#    Updated: 2024/11/06 14:55:20 by agiliber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------------------------------------------------------------------------
# 								HEADER
# ------------------------------------------------------------------------------

NAME = philo
NAME_A = philo.a

# ------------------------------------------------------------------------------
# 								COMPILATION
# ------------------------------------------------------------------------------

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes/ -g3 -pthread
RM = rm -rf
CLEAN = $(MAKE) clean
F_CLEAN = $(MAKE) fclean

RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m
MAGENTA= \033[35m
CYAN   = \033[36m
RESET  = \033[0m

# ------------------------------------------------------------------------------
# 									DIR
# ------------------------------------------------------------------------------

SRC_DIR = src/
OBJ_DIR = obj/
DEP_DIR = dep/

# ------------------------------------------------------------------------------
# 									FILES
# ------------------------------------------------------------------------------

SRC = ft_utils_init.c philo.c ft_init_struct.c ft_print_utils.c routine_philo.c

SRCF = $(addprefix $(SRC_DIR), $(SRC))
OBJ = $(addprefix $(OBJ_DIR), $(SRC:%.c=%.o))
DEPF = $(addprefix $(DEP_DIR), $(OBJ:%.o=%.d))

DEP = $(OBJ:%.o=%.d)

# ------------------------------------------------------------------------------
# 									COMMANDS
# ------------------------------------------------------------------------------

all : $(NAME)

.SILENT : $(NAME) $(NAME_A) $(OBJ) $(OBJ_DIR) $(SRC) $(SRC_DIR) $(DEP) $(DEP_DIR)
	$(CLEAN) $(F_CLEAN)

$(NAME) : $(NAME_A) $(OBJ)
	echo "${CYAN}Compiling Philosophers...${RESET}"
	$(CC) $(CFLAGS) $(OBJ) $(NAME_A) -o $@
	echo "${GREEN}Succes!!!${RESET}"

$(NAME_A) : $(OBJ)
	ar rc $(NAME_A) $(OBJ)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR) $(DEP_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ -MF $(DEP_DIR)$*.d

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(DEP_DIR) :
	mkdir -p $(DEP_DIR)

clean:
	@echo "${RED}Cleaning Philosophers...${RESET}"
	$(RM) $(OBJ_DIR)
	$(RM) $(DEP_DIR)
	@echo "${GREEN}Succes!!!${RESET}"

fclean: clean
	echo "${RED}Cleaning executable files...${RESET}"
	rm -f $(NAME_A) $(NAME)
	echo "${GREEN}Succes!!!${RESET}"

re : fclean all

.PHONY : all clean fclean re

-include $(DEP)
