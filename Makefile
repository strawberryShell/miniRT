# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 11:02:22 by sehhong           #+#    #+#              #
#    Updated: 2022/05/10 15:24:39 by sehhong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# 수정필요....ㅠㅠ 간지나게 하고싶다...

NAME 		= miniRT

SRCS_DIR	= ./srcs/
SRCS		= $(addprefix $(SRCS_DIR), \
				main.c \
				)
OBJS		= $(SRCS:.c=.o)

ifdef DEBUG
	CFLAGS = -g3 -fsanitize=address
else
	CFLAGS = -Wall -Wextra -Werror
endif

CC			= cc
RM			= rm -f
INCDIR		= -I./includes/

LIBMLXDIR	= ./lib/mlx/
LIBMLX		= $(LIBMLXDIR)libmlx.dylib
LIBMLXINC	= -I$(LIBMLXDIR)

LIBFTDIR	= ./lib/libft/
LIBFT		= $(LIBFTDIR)libft.a
LIBFTINC	= -I$(LIBFTDIR)includes

ARCH := $(shell arch)
ifeq ($(ARCH), arm64)
	ARCH_VER = arch -x86_64
endif

all : $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCDIR) $(LIBMLXINC) $(LIBFTINC) -o $@ -c $<

$(NAME) : $(OBJS) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) $(LIBFT) $(LIBMLX) -framework OpenGL -framework Appkit -o $@ $^
	install_name_tool -change libmlx.dylib $(LIBMLX) $(NAME)

$(LIBFT) :
	$(ARCH_VER) make -C $(LIBFTDIR) bonus

$(LIBMLX) :
	$(ARCH_VER) make -C $(LIBMLXDIR) 

clean:
	#make -C $(LIBFTDIR) clean
	#make -C $(LIBMLXDIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	#make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re