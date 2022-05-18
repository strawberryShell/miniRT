/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:10:00 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/18 15:59:12 by sehhong          ###   ########.fr       */
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
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	dir;
}	t_ray;

typedef struct s_camera
{
	t_vec	pos;
	t_vec	n_vector;
	double	foc_len;
}	t_camera;

typedef struct s_amb
{
	double	b_ratio;
	t_vec	color;
}	t_amb;

typedef struct s_light
{
	t_vec			pos;
	double			b_ratio;
	t_vec			color;
	struct s_light	*next;
}	t_light;

typedef struct s_sp
{
	t_vec	centre;
	double	radius;
	t_vec	color;
}	t_sp;

typedef struct s_pl
{
	t_vec	point;
	t_vec	n_vector;
	t_vec	color;
}	t_pl;

typedef struct s_cy
{
	t_vec	point;
	t_vec	n_vector;
	double	radius;
	double	height;
	t_vec	color;
}	t_cy;

typedef struct s_obj
{
	t_otype			type;
	void			*data;
	struct s_obj	*next;
}	t_obj;

//poi = point of intersection(교점)
typedef struct s_poi
{
	double	t;
	t_vec	poi;
	t_obj	*obj;
}	t_poi;

typedef struct s_box
{
	void		*mlx;
	void		*win;
	t_camera	*camera;
	t_img		frame;
	t_vec		top_left;
	t_light		*lights;
	t_amb		*amb_light;
	t_obj		*objs;
}	t_box;

#endif