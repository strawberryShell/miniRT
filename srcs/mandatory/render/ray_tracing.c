/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:20:41 by jiskim            #+#    #+#             */
/*   Updated: 2022/06/01 21:37:36 by jiskim           ###   ########.fr       */
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
		/**
			else if (cur->type == CYLINDER)
			shoot_ray_cy(vec, cur);
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
				printf("camera is in object\n");
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