# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/10 11:45:20 by dapereir          #+#    #+#              #
#    Updated: 2022/12/22 14:04:43 by dapereir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
AR				=	ar rcs
RM				=	rm -f

SRCS			=	char/ft_isalpha.c\
					char/ft_isdigit.c\
					char/ft_isalnum.c\
					char/ft_isascii.c\
					char/ft_isprint.c\
					char/ft_toupper.c\
					char/ft_tolower.c\
					\
					mem/ft_memset.c\
					mem/ft_bzero.c\
					mem/ft_memcpy.c\
					mem/ft_memmove.c\
					mem/ft_memchr.c\
					mem/ft_memcmp.c\
					mem/ft_calloc.c\
					mem/ft_free.c\
					\
					str/ft_strlen.c\
					str/ft_strlcpy.c\
					str/ft_strlcat.c\
					str/ft_strchr.c\
					str/ft_strrchr.c\
					str/ft_strncmp.c\
					str/ft_strnstr.c\
					str/ft_atoi.c\
					str/ft_strdup.c\
					str/ft_strndup.c\
					str/ft_substr.c\
					str/ft_strjoin.c\
					str/ft_strtrim.c\
					str/ft_split.c\
					str/ft_itoa.c\
					str/ft_strmapi.c\
					str/ft_striteri.c\
					\
					write/ft_putchar_fd.c\
					write/ft_putchar.c\
					write/ft_putstr_fd.c\
					write/ft_putstr.c\
					write/ft_putendl_fd.c\
					write/ft_putendl.c\
					write/ft_putnbr_fd.c\
					write/ft_putnbr.c\
					\
					lst/ft_lstnew.c\
					lst/ft_lstadd_front.c\
					lst/ft_lstsize.c\
					lst/ft_lstlast.c\
					lst/ft_lstadd_back.c\
					lst/ft_lstdelone.c\
					lst/ft_lstclear.c\
					lst/ft_lstiter.c\
					lst/ft_lstmap.c\
					\
					gnl/ft_gnl.c\
					\
					printf/ft_print_c.c\
					printf/ft_print_s.c\
					printf/ft_print_i.c\
					printf/ft_print_u.c\
					printf/ft_print_x.c\
					printf/ft_print_p.c\
					printf/ft_printf.c\

OBJS			=	$(SRCS:.c=.o)

INCLUDES_DIR	=	./include
INCLUDES		=	$(INCLUDES_DIR)/libft.h

%.o:			%.c Makefile $(INCLUDES)
				$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $@

.PHONY: all
all:			$(NAME)

$(NAME):		$(OBJS)
				$(AR) $(NAME) $(OBJS)

.PHONY: clean
clean:
				$(RM) $(OBJS)

.PHONY: fclean
fclean:			clean
				$(RM) $(NAME)

.PHONY: re
re:				fclean
				$(MAKE) all
