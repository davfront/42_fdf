# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dapereir <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 16:34:41 by dapereir          #+#    #+#              #
#    Updated: 2022/12/14 16:34:45 by dapereir         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME				=	fdf

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror
RM					=	rm -rf

SRCS_FILES			=	color.c\
						point.c\
						draw.c\
						fdf.c\

SRCS_DIR			=	./src
SRCS				=	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

OBJS_FILES			=	$(SRCS_FILES:.c=.o)
OBJS_DIR			=	./obj
OBJS				=	$(addprefix $(OBJS_DIR)/, $(OBJS_FILES))

HEADER_DIR			=	./includes
HEADER				=	$(HEADER_DIR)/fdf.h
HEADER_INC			=	-I $(HEADER_DIR)

MLX_DIR				=	./minilibx-macos
MLX					=	$(MLX_DIR)/libmlx.a
MLX_INC				=	-I $(MLX_DIR)
MLX_FLAGS			=	-L $(MLX_DIR) -l mlx -framework OpenGL -framework AppKit

.PHONY: all
all:				$(NAME)

$(OBJS_DIR):
					mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c Makefile $(OBJS_DIR) $(MLX)
					$(CC) $(CFLAGS) $(MLX_INC) $(HEADER_INC) -c $< -o $@

$(NAME):			$(OBJS) $(MLX)
					$(CC) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(MLX):
					$(MAKE) -C $(MLX_DIR)

.PHONY: clean
clean:
					$(RM) $(OBJS_DIR)

.PHONY: fclean
fclean:				clean
					$(RM) $(NAME)
					$(MAKE) -C $(MLX_DIR) clean

.PHONY: re
re:					fclean
					$(MAKE) all
					$(MAKE) -C $(MLX_DIR) all
