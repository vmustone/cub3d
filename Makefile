# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/02 07:43:12 by vmustone          #+#    #+#              #
#    Updated: 2023/11/02 08:18:22 by vmustone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Name = cub3d

Libft = libft/libft.a

Flags = -Wall -Werror -Wextra

Src = main.c

Obj = $(Src:%.c=%.o)

all: $(Name) $(Libft)

$(Libft):
	make -C libft

$(Name): $(Obj) $(Libft)
	cc $(Flags) $(Obj) $(Libft) -o $(Name)

clean:
	rm -f $(Obj)
	make clean -C libft

fclean: clean
	rm -f $(Name) $(Libft)

re: fclean all

.phony: all clean fclean re