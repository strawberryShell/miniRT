/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 10:31:54 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/30 11:08:28 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_BONUS_H
# define STRUCTURE_BONUS_H

typedef enum e_otype
{
	SPHERE = 0,
	PLANE,
	CYLINDER,
	CONE,
	ELSE
}	t_otype;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef t_vec t_color;
typedef t_vec t_point;

typedef struct s_cam
{
	double	foc_len;
	t_point	pos;
	t_vec	n_vector;
}	t_cam;

typedef struct s_light
{
	double			b_ratio;
	t_point			pos;
	t_color			color;
	struct s_light	*next;
}	t_light;

typedef struct s_sp
{
	double	radius;
	t_point	center;
	t_color	color;
}	t_sp;

typedef struct s_pl
{
	t_point	point;
	t_vec	n_vector;
	t_color	color;
}	t_pl;

typedef struct s_cy
{
	double	radius;
	double	height;
	t_point	point;
	t_vec	n_vector;
	t_color	color;
}	t_cy;

// 원뿔(cone)
typedef struct s_cn
{
	double	height;
	double	radius;
	t_point	point;
	t_vec	n_vector;
	t_color	color;
}	t_cn;

typedef struct s_obj
{
	t_otype			type;
	void			*data;
	struct s_obj	*next;
}	t_obj;

typedef struct s_poi
{
	double	t;
	t_point	poi;
	t_obj	*obj;
}	t_poi;

typedef struct s_box
{
	void	*mlx;
	void	*win;
	t_color	*amb_light;
	t_cam	*cam;
	t_light	*lights;
	t_obj	*objs;
	t_point	top_left;
	t_img	frame;
}	t_box;

#endif
