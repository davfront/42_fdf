# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 16:34:41 by dapereir          #+#    #+#              #
#    Updated: 2023/01/16 22:06:35 by dapereir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	fdf

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror
RM					=	rm -rf

SRCS_FILES			=	\
						utils/fdf_open_file.c\
						utils/fdf_close_file.c\
						utils/fdf_error_exit.c\
						utils/fdf_get_hex_char_value.c\
						\
						read/fdf_get_input.c\
						read/fdf_get_map_size.c\
						read/fdf_alloc_map_values.c\
						read/fdf_get_map_values.c\
						read/fdf_get_map_computed_values.c\
						read/fdf_read_map.c\
						read/fdf_free_map.c\
						\
						color/fdf_color_rgb.c\
						color/fdf_color_by_rgb.c\
						color/fdf_color_mix.c\
						\
						img/fdf_new_pixel.c\
						img/fdf_vertice_to_pixel.c\
						img/fdf_swap_pixels.c\
						img/fdf_draw_pixel.c\
						img/fdf_draw_line.c\
						img/fdf_draw_triangle.c\
						img/fdf_init_z_buffer.c\
						\
						matrix/fdf_matrix_copy.c\
						matrix/fdf_matrix_multiply.c\
						matrix/fdf_matrix_init.c\
						matrix/fdf_matrix_scale.c\
						matrix/fdf_matrix_translate.c\
						matrix/fdf_matrix_rotate_x.c\
						matrix/fdf_matrix_rotate_y.c\
						matrix/fdf_matrix_transform_point.c\
						\
						viewer/fdf_init_ui.c\
						viewer/fdf_set_view.c\
						viewer/fdf_init_viewer.c\
						viewer/fdf_hooks.c\
						viewer/fdf_hooks_key.c\
						viewer/fdf_hooks_mouse.c\
						viewer/fdf_update_proj.c\
						viewer/fdf_alloc_map_proj.c\
						viewer/fdf_get_map_proj.c\
						viewer/fdf_free_map_proj.c\
						viewer/fdf_draw_face.c\
						viewer/fdf_draw_map.c\
						viewer/fdf_draw_help_utils.c\
						viewer/fdf_draw_help.c\
						viewer/fdf_render_frame.c\
						viewer/fdf_start_viewer.c\
						\
						fdf_free_all.c\
						fdf_exit.c\
						main.c

SRCS_DIR			=	./src
SRCS				=	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

OBJS_FILES			=	$(SRCS_FILES:.c=.o)
OBJS_DIR			=	./obj
OBJS				=	$(addprefix $(OBJS_DIR)/, $(OBJS_FILES))

HEADER_DIR			=	./include
HEADER				=	$(HEADER_DIR)/fdf.h $(HEADER_DIR)/key_linux.h $(HEADER_DIR)/key_macos.h
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

FT_DIR				=	./libft
FT					=	$(FT_DIR)/libft.a
FT_INC				=	-I $(FT_DIR)/include
FT_FLAGS			=	-L $(FT_DIR) -l ft

.PHONY: all
all:				$(NAME)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c Makefile $(MLX) $(FT) $(HEADER)
					mkdir -p $(@D)
					$(CC) $(CFLAGS) $(MLX_OBJ_FLAGS) $(FT_INC) -c $< -o $@

$(NAME):			$(OBJS) $(MLX) $(FT)
					$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(FT_FLAGS) -o $(NAME)

$(MLX):
					$(MAKE) -C $(MLX_DIR)

$(FT):
					$(MAKE) -C $(FT_DIR)

.PHONY: clean
clean:
					$(RM) $(OBJS_DIR)
					$(MAKE) -C $(FT_DIR) clean

.PHONY: fclean
fclean:				clean
					$(RM) $(NAME)
					$(MAKE) -C $(MLX_DIR) clean
					$(MAKE) -C $(FT_DIR) fclean

.PHONY: re
re:					fclean
					$(MAKE) all
