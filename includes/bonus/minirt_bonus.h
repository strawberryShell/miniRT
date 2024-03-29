/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 10:30:56 by sehhong           #+#    #+#             */
/*   Updated: 2022/06/08 21:22:35 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# define SCN_WIDTH	1200
# define SCN_HEIGHT	1000
# define POINT		0
# define COLOR		1
# define VECTOR		2
# define DARKNESS 	-42
# define KEY_ESC	53
# define CLICK_RED	17

# include <math.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"
# include "mlx.h"
# include "structure_bonus.h"

/* ctrl_mlx */
void	init_mlx_attr(t_box *box);
int		press_esc(int key_num, t_box *box);
int		click_red(t_box *box);

/* render */
void	ray_tracing(t_box *box);
int		phong_lighting(t_poi *poi, t_box *box);
t_phong	get_phong_vecs(t_poi *poi, t_box *box);
double	shoot_ray_sp(t_vec *ray, t_sp *sp, t_point *start, t_ptype *type);
double	shoot_ray_pl(t_vec *ray, t_pl *pl, t_ptype *type);
double	shoot_ray_cy(t_vec *ray, t_cy *cy, t_point *start, t_ptype *type);
double	shoot_ray_cn(t_vec *ray, t_cn *cn, t_point *start, t_ptype *type);
double	get_root(t_vec *coef);
int		calc_color(int r, int g, int b);
int		is_shadow(t_poi *poi, t_box *box, t_vec *light_vec);
t_color	*get_obj_color(t_poi *poi);
double	shoot_ray_obj(t_obj *obj, t_vec *ray, t_vec *cam_pos, t_ptype *type);

/* parse */
void	read_file(t_box *box, char *f_name);
double	ft_atod(char *str, char *ele);
void	add_obj(t_box *box, t_otype type, void *obj);
void	validate_arr(char **arr, int info_num, char *ele);
t_vec	parse_vector(char *str, char *ele, int vec_type);
void	parse_ambient(t_box *box, char **arr);
void	parse_light(t_box *box, char **arr);
void	parse_cam(t_box *box, char **arr);
void	parse_sphere(t_box *box, char **arr);
void	parse_plane(t_box *box, char **arr);
void	parse_cylinder(t_box *box, char **arr);
void	parse_cone(t_box *box, char **arr);

/* xform */
void	fill_tr_matrix(t_cam *cam, double *matrix);
void	xform_coord(t_box *box);
t_vec	xform_vec(double *m, t_vec vec);
t_vec	xform_point(double *m, t_vec point);

/* utils */
void	exit_with_err(char *err_str, char *err_str2);
int		is_between(double min, double max, double x);
void	free_str_arr(char ***arr);

/* vector_utils */
t_vec	new_vec(double x, double y, double z);
double	get_vec_len(t_vec vec);
double	dot_vecs(t_vec vec1, t_vec vec2);
t_vec	cross_vecs(t_vec vec1, t_vec vec2);
t_vec	scale_vec(t_vec vec, double k);
t_vec	add_vecs(t_vec vec1, t_vec vec2);
t_vec	subtract_vecs(t_vec vec1, t_vec vec2);
int		cmp_vec(t_vec vec1, t_vec vec2);
t_vec	multiply_vecs(t_vec vec1, t_vec vec2);
t_vec	normalize_vec(t_vec vec);

#endif
