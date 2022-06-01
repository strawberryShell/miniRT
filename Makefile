# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 11:02:22 by sehhong           #+#    #+#              #
#    Updated: 2022/05/30 17:01:39 by sehhong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 				= miniRT

SRCS_M_DIR			= ./srcs/mandatory/
SRCS_M_PARSE_DIR	= ./srcs/mandatory/parse/
SRCS_M_XFORM_DIR	= ./srcs/mandatory/transform/
SRCS_M_RENDER_DIR	= ./srcs/mandatory/render/
SRCS_M_CTLMLX_DIR		= ./srcs/mandatory/ctrl_mlx/

SRCS_M_PARSE		= $(addprefix $(SRCS_M_PARSE_DIR), \
					parse_obj.c \
					parse_setting.c \
					read_file.c \
					parse_utils.c \
					)

SRCS_M_XFORM		= $(addprefix $(SRCS_M_XFORM_DIR), \
					fill_tr_matrix.c \
					transform_coord.c \
					transform_utils.c \
					)

SRCS_M_RENDER		= $(addprefix $(SRCS_M_RENDER_DIR), \
					ray_tracing.c \
					)

SRCS_M_CTLMLX		= $(addprefix $(SRCS_M_CTLMLX_DIR), \
					ctrl_mlx_hook.c \
					init_mlx_attr.c \
					)

SRCS_M				= $(addprefix $(SRCS_M_DIR), \
					main.c \
					utils.c \
					vector_utils.c \
					)

SRCS_M				+= $(SRCS_M_PARSE) $(SRCS_M_XFORM) $(SRCS_M_RENDER) \
					$(SRCS_M_CTLMLX)

OBJS_M				= $(SRCS_M:.c=.o)

SRCS_B_DIR			= ./srcs/bonus/
SRCS_B_PARSE_DIR	= ./srcs/bonus/parse/
SRCS_B_XFORM_DIR	= ./srcs/bonus/transform/
SRCS_B_RENDER_DIR	= ./srcs/bonus/render/
SRCS_B_CTLMLX_DIR	= ./srcs/bonus/ctrl_mlx/

SRCS_B_PARSE		= $(addprefix $(SRCS_B_PARSE_DIR), \
					parse_obj_bonus.c \
					parse_setting_bonus.c \
					read_file_bonus.c \
					parse_utils_bonus.c \
					)

SRCS_B_XFORM		= $(addprefix $(SRCS_B_XFORM_DIR), \
					fill_tr_matrix_bonus.c \
					transform_coord_bonus.c \
					transform_utils_bonus.c \
					)

SRCS_B_RENDER		= $(addprefix $(SRCS_B_RENDER_DIR), \
					ray_tracing_bonus.c \
					)

SRCS_B_CTLMLX			= $(addprefix $(SRCS_B_CTLMLX_DIR), \
					ctrl_mlx_hook.c \
					init_mlx_attr_bonus.c \
					)

SRCS_B				= $(addprefix $(SRCS_B_DIR), \
					main_bonus.c \
					utils_bonus.c \
					vector_utils_bonus.c \
					)

SRCS_B				+= $(SRCS_B_PARSE) $(SRCS_B_XFORM) $(SRCS_B_RENDER) \
					$(SRCS_B_CTLMLX)

OBJS_B				= $(SRCS_B:.c=.o)

ifdef DEBUG
	CFLAGS 	= -g3 -fsanitize=address
else
	CFLAGS	= -Wall -Wextra -Werror
endif

ifdef WITH_BONUS
	OBJS 	= $(OBJS_B)
	INCDIR 	= -I./includes/bonus/
else
	OBJS	= $(OBJS_M)
	INCDIR	= -I./includes/mandatory/
endif

CC			= cc
RM			= rm -f

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
	$(RM) $(OBJS_M) $(OBJS_B)

fclean: clean
	$(RM) $(NAME)

bonus:
	@make WITH_BONUS=1 all

debug: fclean
	@make DEBUG=1

re: fclean all

.PHONY: all clean fclean bonus re
