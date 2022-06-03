/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:10:00 by sehhong           #+#    #+#             */
/*   Updated: 2022/06/03 18:04:29 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef enum e_otype //도형 구분
{
	SPHERE = 0,
	PLANE,
	CYLINDER,
	ELSE
}	t_otype;

typedef enum e_ptype
{
	SPHERE_GENERAL = 0,
	PLANE_GENERAL,
	CYLINDER_TOP,
	CYLINDER_BOTTOM,
	CYLINDER_SIDE,
	CONE_BOTTOM,
	CONE_SIDE,
}	t_ptype;

typedef enum e_stype
{
	TOP = 0,
	BOTTOM,
	SIDE,
	TOP_SIDE,
	BOTTOM_SIDE,
}	t_stype;

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
	t_stype	side;
	t_point	top;
	t_point	bottom;
	t_vec	n_vector;
	t_color	color;
}	t_cy;

typedef struct s_obj
{
	t_otype			type;
	void			*data;
	struct s_obj	*next;
}	t_obj;

typedef struct s_poi
{
	t_ptype type; // 구, 평면, 원기둥뚜겅, 바닥, 옆면
	t_point	point;
	void 	*data;
}	t_poi;

typedef struct s_phong
{
	double	cos_theta;
	t_vec	light_vec;
	t_vec	normal_vec;
	t_vec	cam_vec;
	t_vec	reflect_vec;
}	t_phong;

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
