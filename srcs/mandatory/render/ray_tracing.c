/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:20:41 by jiskim            #+#    #+#             */
/*   Updated: 2022/06/04 21:49:21 by sehhong          ###   ########.fr       */
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

double	shoot_ray_sp(t_vec *ray, t_sp *sp, t_point *start, t_ptype *type)
{
	t_vec	coefficient; //a, b, c
	t_vec	center_start;

	if (type)
		*type = SPHERE_GENERAL;
	center_start = subtract_vecs(*start, sp->center);
	coefficient.x = dot_vecs(*ray, *ray);
	coefficient.y = 2 * dot_vecs(center_start, *ray);
	coefficient.z = dot_vecs(center_start, center_start) - pow(sp->radius, 2);
	return (get_root(&coefficient));
}

double	shoot_ray_pl(t_vec *ray, t_pl *pl, t_ptype *type)
{
	double	scalar;

	if (type)
		*type = PLANE_GENERAL;
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
			t = shoot_ray_sp(ray, (t_sp *)cur->data, &box->cam->pos, &type);
		else if (cur->type == PLANE)
			t = shoot_ray_pl(ray, (t_pl *)cur->data, &type);
		else if (cur->type == CYLINDER)
			t = shoot_ray_cy(ray, (t_cy *)cur->data, &box->cam->pos, &type);
		else
			t = shoot_ray_cn(ray, (t_cn *)cur->data, &box->cam->pos, &type);
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

void	ray_tracing(t_box *box)
{
	t_point	cur;
	int		color;

	cur = box->top_left;
	color = 0;
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
