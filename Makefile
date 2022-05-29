# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 11:02:22 by sehhong           #+#    #+#              #
#    Updated: 2022/05/29 16:36:51 by jiskim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# 수정필요....ㅠㅠ 간지나게 하고싶다...

NAME 		= miniRT

SRCS_DIR		= ./srcs/
SRCS_PARSE_DIR	= ./srcs/parse/
SRCS_XFORM_DIR	= ./srcs/transform/
SRCS_RENDER_DIR	= ./srcs/render/
SRCS_INIT_DIR	= ./srcs/initialize/

SRCS_PARSE		= $(addprefix $(SRCS_PARSE_DIR), \
					parse_obj.c \
					parse_setting.c \
					read_file.c \
					parse_utils.c \
					)

SRCS_XFORM		= $(addprefix $(SRCS_XFORM_DIR), \
					fill_tr_matrix.c \
					transform_coord.c \
					transform_utils.c \
					)

SRCS_RENDER		= $(addprefix $(SRCS_RENDER_DIR), \
					ray_tracing.c \
					)

SRCS_INIT		= $(addprefix $(SRCS_INIT_DIR), \
					init_mlx_attr.c \
					)

SRCS			= $(addprefix $(SRCS_DIR), \
					main.c \
					utils.c \
					vector_utils.c \
					)

SRCS			+= $(SRCS_PARSE) $(SRCS_XFORM) $(SRCS_RENDER) $(SRCS_INIT)

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

all : $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCDIR) $(LIBMLXINC) $(LIBFTINC) -o $@ -c $<

$(NAME) : $(OBJS) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) $(LIBFT) $(LIBMLX) -framework OpenGL -framework Appkit -o $@ $^
	install_name_tool -change libmlx.dylib $(LIBMLX) $(NAME)

$(LIBFT) :
	make -C $(LIBFTDIR) bonus

$(LIBMLX) :
	make -C $(LIBMLXDIR)

clean:
	@make -C $(LIBFTDIR) fclean
	@make -C $(LIBMLXDIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

debug: fclean
	@make DEBUG=1

re: fclean all

.PHONY: all clean fclean re
