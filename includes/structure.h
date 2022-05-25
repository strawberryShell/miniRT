/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:10:00 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/25 22:12:52 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef enum e_otype
{
	SPHERE = 0,
	PLANE,
	CYLINDER,
	ELSE
}	t_otype;

typedef struct s_img
{
	void	*img;
	char	*addr;
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
typedef struct s_ray
{
	t_point	origin;
	t_vec	dir;
}	t_ray;

typedef struct s_cam
{
	double	foc_len;
	t_point	pos;
	t_vec	n_vector;
}	t_cam;

/* ambient */
typedef struct s_amb
{
	double	b_ratio;
	t_color	color;
}	t_amb;

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

typedef struct s_obj
{
	t_otype			type;
	void			*data;
	struct s_obj	*next;
}	t_obj;

/* poi = point of intersection(교점) */
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
	t_cam	*cam;
	t_img	frame;
	t_point	top_left;
	t_light	*lights;
	t_amb	*amb_light;
	t_obj	*objs;
}	t_box;

#endif
