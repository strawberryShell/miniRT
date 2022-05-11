/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:03:31 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/12 00:38:25 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define SCN_WIDTH	800
# define SCN_HEIGHT	400

# include <math.h>
# include <stdlib.h>	//malloc
# include <string.h>		//strerror
# include <sys/errno.h>	//errno
# include <fcntl.h>		//open
# include <unistd.h>	//close
# include <string.h> 	//s
# include "libft.h"
# include "mlx.h"
# include "structure.h"

/* parse */
void	read_file(t_box *box, char *f_name);
double	ft_atod(char *str, char *ele);
void	add_obj(t_box *box, t_otype type, void *obj);
void	validate_arr(char **arr, int info_num, char *ele);
t_color	parse_color(char *str, char *ele);
t_point	parse_point(char *str, char *ele);
t_vec	parse_vector(char *str, char *ele);
void	parse_ambient(t_box *box, char **arr);
void	parse_light(t_box *box, char **arr);
void	parse_camera(t_box *box, char **arr);
void	parse_sphere(t_box *box, char **arr);
void	parse_plane(t_box *box, char **arr);
void	parse_cylinder(t_box *box, char **arr);

/* utils */
void	exit_with_err(char *err_str, char *err_str2);
int	is_between(double min, double max, double x);

/* vector_utils */
double	vec_len(t_vec vec);
double	vec_dot(t_vec vec1, t_vec vec2);
void	free_str_arr(char ***arr);

#endif