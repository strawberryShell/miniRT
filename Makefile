# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 11:02:22 by sehhong           #+#    #+#              #
#    Updated: 2022/05/16 17:37:17 by sehhong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# 수정필요....ㅠㅠ 간지나게 하고싶다...

NAME 		= miniRT

SRCS_DIR		= ./srcs/
SRCS_PARSE_DIR	= ./srcs/parse/
SRCS_XFORM_DIR	= ./srcs/transform/
SRCS_RENDER_DIR	= ./srcs/render/

SRCS_PARSE		= $(addprefix $(SRCS_PARSE_DIR), \
					parse_obj.c \
					parse_setting.c \
					read_file.c \
					utils.c \
					)

SRCS_XFORM		= $(addprefix $(SRCS_XFORM_DIR), \
					fill_tr_matrix.c \
					transform_coord.c \
					transform_utils.c \
					)

SRCS_RENDER		= $(addprefix $(SRCS_RENDER_DIR), \
					find_closest_poi.c \
					get_root.c \
					paint_frame.c \
					sum_diff_light.c \
					sum_spec_light.c \
					)

SRCS			= $(addprefix $(SRCS_DIR), \
					main.c \
					utils.c \
					vector_utils.c \
					)

SRCS			+= $(SRCS_PARSE) $(SRCS_XFORM) $(SRCS_RENDER)

OBJS			= $(SRCS:.c=.o)

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
	MAKE_VER = arch -x86_64 make
else ifeq ($(ARCH), i386)
	MAKE_VER = make
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
	make -C $(LIBFTDIR) clean
	make -C $(LIBMLXDIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re