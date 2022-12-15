# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 16:34:41 by dapereir          #+#    #+#              #
#    Updated: 2022/12/15 22:52:32 by dapereir         ###   ########.fr        #
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

HEADER_DIR			=	./include
HEADER				=	$(HEADER_DIR)/fdf.h
HEADER_INC			=	-I $(HEADER_DIR)

# Detect OS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
#	Linux
	MLX_DIR				=	./minilibx-linux
	MLX					=	$(MLX_DIR)/libmlx.a
	MLX_INC				=	-I $(MLX_DIR)
	MLX_OBJ_FLAGS		=	-I/usr/include $(HEADER_INC) $(MLX_INC) -O3
	MLX_FLAGS			=	-L $(MLX_DIR) -l mlx -L/usr/lib $(MLX_INC) -lXext -lX11 -lm -lz
else
#	MacOS
	MLX_DIR				=	./minilibx-macos
	MLX					=	$(MLX_DIR)/libmlx.a
	MLX_INC				=	-I $(MLX_DIR)
	MLX_OBJ_FLAGS		=	$(MLX_INC) $(HEADER_INC)
	MLX_FLAGS			=	-L $(MLX_DIR) -l mlx -framework OpenGL -framework AppKit

endif

.PHONY: all
all:				$(NAME)

$(OBJS_DIR):
					mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c Makefile $(OBJS_DIR) $(MLX)
					$(CC) $(CFLAGS) $(MLX_OBJ_FLAGS) -c $< -o $@

$(NAME):			$(OBJS) $(MLX)
					$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

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
