NAME			=	fdf

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
AR				=	ar rcs
RM				=	rm -f

SRCS			=	fdf.c\

OBJS			=	$(SRCS:.c=.o)

MLX_DIR			=	./mlx
MLX				=	$(MLX_DIR)/libmlx.a
MLX_FLAGS		=	-Lmlx -lmlx -framework OpenGL -framework AppKit

%.o:			%.c Makefile $(MLX)
				$(CC) $(CFLAGS) -I $(MLX_DIR) -c $< -o $@

.PHONY: all
all:			$(NAME)

$(NAME):		$(OBJS) $(MLX)
				$(CC) $(OBJS) $(MLX_FLAGS) -o $(NAME)


.PHONY: mlx
mlx:			$(MLX)

$(MLX):
				$(MAKE) -C $(MLX_DIR)

.PHONY: clean
clean:
				$(RM) $(OBJS)

.PHONY: fclean
fclean:			clean
				$(RM) $(NAME)
				$(MAKE) -C $(MLX_DIR) clean

.PHONY: re
re:				fclean
				$(MAKE) all
				$(MAKE) -C $(MLX_DIR) all