/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:20:41 by jiskim            #+#    #+#             */
/*   Updated: 2022/06/02 16:44:18 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	get_root(t_vec *coeffient)
{
	double	d;
	double	t;

	d = pow(coeffient->y, 2) - 4 * coeffient->x * coeffient->z;
	if (coeffient->x == 0 || d < 0)
		t = -1;
	else
	{
		t = (-coeffient->y - sqrt(d)) / (2 * coeffient->x);
		if (t < 0)
		{
			t = (-coeffient->y + sqrt(d)) / (2 * coeffient->x);
			if (t > 0)
				t = DARKNESS;
			else
				t = -1;
		}
	}
	return (t);
}

double	shoot_ray_sphere(t_vec *ray, t_sp *sp, t_point *start)
{
	t_vec	coeffient; //a, b, c
	t_vec	center_start;

	center_start = subtract_vecs(*start, sp->center);
	coeffient.x = dot_vecs(*ray, *ray);
	coeffient.y = 2 * dot_vecs(center_start, *ray);
	coeffient.z = dot_vecs(center_start, center_start) - pow(sp->radius, 2);
	return (get_root(&coeffient));
}

double	shoot_ray_plane(t_vec *ray, t_pl *pl)
{
	double	scalar;

	scalar = dot_vecs(*ray, pl->n_vector);
	if (scalar == 0) //명륜진사갈비
		return (0);
	return (dot_vecs(pl->point, pl->n_vector) / scalar);
}

int		shoot_ray(t_vec *vec, t_box *box)
{
	t_obj	*cur;
	t_poi	poi;
	double	closest_t;
	double	t;
	t_ptype type = 0;

	double	cos_theta;
	t_stype side;

	cur = box->objs;
	closest_t = INFINITY;
	while (cur != 0)
	{
		if (cur->type == SPHERE)
		{
			t = shoot_ray_sphere(vec, (t_sp *)cur->data, &box->cam->pos);
			type = SPHERE_GENERAL;
		}
		else if (cur->type == PLANE)
		{
			t = shoot_ray_plane(vec, (t_pl *)cur->data);
			type = PLANE_GENERAL;
		}
		else if (cur->type == CYLINDER)
		{
			t = shoot_ray_cylinder(vec, (t_cy *)cur->data, &poi);
			//cylinder_top
			//bottom
			//side 
			// 3개의 t값
		}
		
		/**
			...
		 *
		 */
		// 이전에 구한 벡터와 비교
		if (t == DARKNESS)
			return (DARKNESS);
		if (t >= 0)
		{
			if (t == 0)
				return (0);
			if (t < closest_t)
			{
				poi.point = scale_vec(*vec, t);
				closest_t = t;
				poi.data = cur->data;
				poi.type = type;
			}
		}
		cur = cur->next;
	}
	if (closest_t == INFINITY)
		return (0);
	return (phong_lighting(&poi, box));
}

void	set_sideview(t_box *box)
{
	t_obj	*obj;
	double	cos_theta;
	t_stype	side;

	obj = box->objs;
	cos_theta = 0;
	while (obj)
	{
		if (obj->type == CYLINDER)
		{
			cos_theta = dot_vecs(((t_cy *)obj->data)->point, \
				((t_cy *)obj->data)->n_vector);
			if (cos_theta == -1)
				side = TOP;
			else if (cos_theta == 0)
				side = SIDE;
			else if (cos_theta == 1)
				side = BOTTOM;
			else if (cos_theta < 0)
				side = TOP_SIDE;
			else
				side = BOTTOM_SIDE;
			((t_cy *)obj->data)->side = side;
		}
		obj = obj->next;
	}
}

void	ray_tracing(t_box *box)
{
	t_point	cur;
	int		color;

	cur = box->top_left;
	color = 0;
	set_sideview(box);
	while (box->top_left.y - cur.y < SCN_HEIGHT)
	{
		cur.x = box->top_left.x;
		while (cur.x - box->top_left.x < SCN_WIDTH)
		{
			color = shoot_ray(&cur, box);
			if (color == DARKNESS)
			{
				ft_bzero(box->frame.addr, sizeof(box->frame.addr));
				return ;
			}
			box->frame.addr[((int)(box->top_left.y - cur.y) * \
				box->frame.line_len + (int)(cur.x - box->top_left.x) * \
				box->frame.bpp / 8) / 4] = color;
			cur.x++;
		}
		cur.y--;
	}
}
