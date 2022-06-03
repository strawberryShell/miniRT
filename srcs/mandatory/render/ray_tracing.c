/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:20:41 by jiskim            #+#    #+#             */
/*   Updated: 2022/06/03 18:30:12 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// -1, DARKNESS, 양수
double	get_root(t_vec *coefficient)
{
	double	d;
	double	t;

	d = pow(coefficient->y, 2) - 4 * coefficient->x * coefficient->z;
	if (coefficient->x == 0 || d < 0)
		t = -1;
	else
	{
		t = (-coefficient->y - sqrt(d)) / (2 * coefficient->x);
		if (t < 0)
		{
			t = (-coefficient->y + sqrt(d)) / (2 * coefficient->x);
			if (t >= 0)
				t = DARKNESS;
			else
				t = -1;
		}
	}
	return (t);
}

double	shoot_ray_sp(t_vec *ray, t_sp *sp, t_point *start)
{
	t_vec	coefficient; //a, b, c
	t_vec	center_start;

	center_start = subtract_vecs(*start, sp->center);
	coefficient.x = dot_vecs(*ray, *ray);
	coefficient.y = 2 * dot_vecs(center_start, *ray);
	coefficient.z = dot_vecs(center_start, center_start) - pow(sp->radius, 2);
	return (get_root(&coefficient));
}

double	shoot_ray_pl(t_vec *ray, t_pl *pl)
{
	double	scalar;

	scalar = dot_vecs(*ray, pl->n_vector);
	if (scalar == 0) //명륜진사갈비
		return (0);
	return (dot_vecs(pl->point, pl->n_vector) / scalar);
}

int		shoot_ray(t_vec *ray, t_box *box)
{
	t_obj	*cur;
	t_poi	poi;
	double	closest_t;
	double	t;
	t_ptype type;

	cur = box->objs;
	closest_t = INFINITY;
	type = 0;
	while (cur != 0)
	{
		if (cur->type == SPHERE)
		{
			t = shoot_ray_sp(ray, (t_sp *)cur->data, &box->cam->pos);
			type = SPHERE_GENERAL;
		}
		else if (cur->type == PLANE)
		{
			t = shoot_ray_pl(ray, (t_pl *)cur->data);
			type = PLANE_GENERAL;
		}
		//else if (cur->type == CYLINDER)
		//	t = shoot_ray_cy(ray, (t_cy *)cur->data, &poi, &box->cam->pos);
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
				poi.point = scale_vec(*ray, t);
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
			cos_theta = dot_vecs(((t_cy *)obj->data)->bottom, \
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
