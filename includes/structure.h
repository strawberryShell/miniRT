/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:10:00 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/10 23:57:28 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef	struct s_vec3	t_vec;
typedef struct s_vec3 	t_point;
typedef struct s_vec3 	t_color;

typedef enum e_type
{
	AMBIENT = 0,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}	t_type;

typedef	struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

struct	s_vec3
{
	double	x;
	double	y;
	double	z;
};

typedef	struct	s_ray
{
	t_point	origin;
	t_vec	dir;
}	t_ray;

typedef	struct	s_camera
{
	t_point	pos;
	t_vec	n_vector;
	double	foc_len;
}	t_camera;

// typedef struct	s_amb
// {
// 	double	b_ratio;
// 	t_color	color;
// }	t_amb;

typedef	struct	s_light
{
	t_point	pos;
	double	b_ratio;
	t_color	color;
}	t_light;


typedef	struct s_sp
{
	t_point	centre;
	double	radius;
	t_color	color;
}	t_sp;

typedef	struct s_pl
{
	t_point	point;
	t_vec	n_vector;
	t_color	color;
}	t_pl;

typedef struct s_cy
{
	t_point	point;
	t_vec	n_vector;
	double	radius;
	double	height;
	t_color	color;
}	t_cy;

typedef struct	s_obj
{
	t_type			type;
	void			*obj;
	struct s_obj	next;
}	t_obj;

typedef	struct	s_box
{
	void		*mlx;
	void		*win;
	t_camera	camera;
	t_img		frame;
	t_point		top_left;
	t_list		*lights;
	// t_amb		amb_light;
	t_light		amb_light;
	t_obj		*objs;
}	t_box;

#endif