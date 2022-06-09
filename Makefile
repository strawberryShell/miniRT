# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 11:02:22 by sehhong           #+#    #+#              #
#    Updated: 2022/06/09 11:57:13 by jiskim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 				= miniRT

SRCS_M_DIR			= ./srcs/mandatory/
SRCS_M_PARSE_DIR	= ./srcs/mandatory/parse/
SRCS_M_XFORM_DIR	= ./srcs/mandatory/xform/
SRCS_M_RENDER_DIR	= ./srcs/mandatory/render/
SRCS_M_CTLMLX_DIR	= ./srcs/mandatory/ctrl_mlx/
SRCS_M_VECTOR_DIR	= ./srcs/mandatory/vector/

SRCS_M_PARSE		= $(addprefix $(SRCS_M_PARSE_DIR), \
					parse_obj.c \
					parse_setting.c \
					read_file.c \
					parse_utils.c \
					)

SRCS_M_XFORM		= $(addprefix $(SRCS_M_XFORM_DIR), \
					fill_tr_matrix.c \
					xform_coord.c \
					xform_utils.c \
					)

SRCS_M_RENDER		= $(addprefix $(SRCS_M_RENDER_DIR), \
					ray_tracing.c \
					phong_lighting.c \
					shoot_ray_cy.c \
					shoot_ray_cn.c \
					get_phong_vecs.c \
					phong_utils.c \
					shoot_ray_obj.c \
					)

SRCS_M_CTLMLX		= $(addprefix $(SRCS_M_CTLMLX_DIR), \
					ctrl_mlx_hook.c \
					init_mlx_attr.c \
					)

SRCS_M_VECTOR		= $(addprefix $(SRCS_M_VECTOR_DIR), \
					vector_operations.c \
					vector_utils.c \
					)

SRCS_M				= $(addprefix $(SRCS_M_DIR), \
					main.c \
					utils.c \
					)

SRCS_M				+= $(SRCS_M_PARSE) $(SRCS_M_XFORM) $(SRCS_M_RENDER) \
					$(SRCS_M_CTLMLX) $(SRCS_M_VECTOR)

OBJS_M				= $(SRCS_M:.c=.o)

SRCS_B_DIR			= ./srcs/bonus/
SRCS_B_PARSE_DIR	= ./srcs/bonus/parse/
SRCS_B_XFORM_DIR	= ./srcs/bonus/xform/
SRCS_B_RENDER_DIR	= ./srcs/bonus/render/
SRCS_B_CTLMLX_DIR	= ./srcs/bonus/ctrl_mlx/
SRCS_B_VECTOR_DIR	= ./srcs/bonus/vector/

SRCS_B_PARSE		= $(addprefix $(SRCS_B_PARSE_DIR), \
					parse_obj_bonus.c \
					parse_setting_bonus.c \
					read_file_bonus.c \
					parse_utils_bonus.c \
					)

SRCS_B_XFORM		= $(addprefix $(SRCS_B_XFORM_DIR), \
					fill_tr_matrix_bonus.c \
					xform_coord_bonus.c \
					xform_utils_bonus.c \
					)

SRCS_B_RENDER		= $(addprefix $(SRCS_B_RENDER_DIR), \
					ray_tracing_bonus.c \
					phong_lighting_bonus.c \
					shoot_ray_cy_bonus.c \
					shoot_ray_cn_bonus.c \
					get_phong_vecs_bonus.c \
					phong_utils_bonus.c \
					shoot_ray_obj_bonus.c \
					)

SRCS_B_CTLMLX		= $(addprefix $(SRCS_B_CTLMLX_DIR), \
					ctrl_mlx_hook_bonus.c \
					init_mlx_attr_bonus.c \
					)

SRCS_B_VECTOR		= $(addprefix $(SRCS_B_VECTOR_DIR), \
					vector_operations_bonus.c \
					vector_utils_bonus.c \
					)

SRCS_B				= $(addprefix $(SRCS_B_DIR), \
					main_bonus.c \
					utils_bonus.c \
					)


SRCS_B				+= $(SRCS_B_PARSE) $(SRCS_B_XFORM) $(SRCS_B_RENDER) \
					$(SRCS_B_CTLMLX) $(SRCS_B_VECTOR)

OBJS_B				= $(SRCS_B:.c=.o)

ifdef DEBUG
	CFLAGS 	= -g3 -fsanitize=address
else
	CFLAGS	= -Wall -Wextra -Werror
endif

ifdef WITH_BONUS
	OBJS	=	$(OBJS_B)
	INCDIR	=	-I./includes/bonus/
	BONUS	=	bonus
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
	@$(CC) $(CFLAGS) $(INCDIR) $(LIBMLXINC) $(LIBFTINC) -o $@ -c $<
	@echo $(CUT)$(BOLD)$(L_GREEN) Compiling $(BONUS) with $(CFLAGS)...$(RESET)
	@echo $(CUT)$(L_CYAN) [$(notdir $^)] to [$(notdir $@)] $(RESET)
	@printf $(UP)$(UP)

$(NAME) : $(OBJS) $(LIBFT) $(LIBMLX)
	@$(CC) $(CFLAGS) $(LIBFT) $(LIBMLX) -framework OpenGL -framework Appkit -o $@ $^
	@install_name_tool -change libmlx.dylib $(LIBMLX) $(NAME)
	@printf $(BOLD)$(L_PURPLE) 🍉 Mini Ray Tracing program is $(L_WHITE)ready!!$(RESET)

$(LIBFT) :
	@make -C $(LIBFTDIR) bonus

$(LIBMLX) :
	@make -C $(LIBMLXDIR)

clean:
	@make -C $(LIBFTDIR) fclean
	@make -C $(LIBMLXDIR) clean
	@$(RM) $(OBJS_M) $(OBJS_B)
	@echo $(BOLD)$(YELLOW) 🗒 object files have been $(L_RED)cleaned....💫$(RESET)

fclean: clean
	@$(RM) $(NAME)
	@echo $(BOLD)$(YELLOW) 🍉 Mini Ray Tracing has been $(L_RED)cleaned....💫$(RESET)


bonus:
	@make WITH_BONUS=1 all

debug: fclean
	@make DEBUG=1

dbonus:
	@make WITH_BONUS=1 debug

re: fclean all

.PHONY: all clean fclean bonus re

######################### Color #########################
GREEN="\033[32m"
L_GREEN="\033[1;32m"
YELLOW="\033[33m"
RED="\033[31m"
L_RED="\033[1;31m"
BLUE="\033[34m"
L_BLUE="\033[1;34m"
MUTED="\033[130m"
RESET="\033[0m"
BOLD="\033[1m"
L_PURPLE="\033[1;35m"
L_CYAN="\033[1;36m"
L_GRAY="\033[1;37m"
L_WHITE="\033[1;38m"
L_YELLOW="\033[1;93m"
UP = "\033[A"
DOWN = "\033[B"
RIGHT = "\033[C"
LEFT = "\033[D"
CUT = "\033[K"
SAVE = "\033[s"
RESTORE = "\033[u"
