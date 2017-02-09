#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/05/28 16:38:24 by ale-batt          #+#    #+#             *#
#*   Updated: 2016/10/28 10:46:39 by ale-batt         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

SRC = malloc.c

OBJ = $(SRC:%.c=obj/%.o)

CXX = gcc
CXXFLAGS = -g -Wall -Werror -Wextra

INC = -I includes
LIB = libft/

all: $(NAME)

$(NAME): obj $(OBJ)
	@make -s -C $(LIB)
	@$(CXX) $(CXXFLAGS) -shared -o $@ $(OBJ) $(INC) -L$(LIB) -lft
	@ln -sf $(NAME) libft_malloc.so

obj/%.o: %.c
	$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $< -I$(LIB)

obj:
	mkdir -p obj/

clean:
	@rm -rf obj

fclean: clean
	@make clean -s -C $(LIB)
	@rm -rf $(NAME)

re: fclean all
	@make re -s -C $(LIB)

.PHONY: fclean all clean re