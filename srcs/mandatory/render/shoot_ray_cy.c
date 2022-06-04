/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_ray_cy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:23:03 by jiskim            #+#    #+#             */
/*   Updated: 2022/06/04 12:27:57 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	shoot_ray_top(t_vec *ray, t_cy *cy, t_point *start)
{
	t_vec	v;
	double	t;
	t_point	poi;

	v = subtract_vecs(cy->top, *start);
	t = dot_vecs(v, cy->n_vector) / dot_vecs(*ray, cy->n_vector);
	if (t < 0)
		return (-1);
	poi = add_vecs(*start, scale_vec(*ray, t));
	if (get_vec_len(subtract_vecs(poi, cy->top)) < cy->radius)
		return (t);
	return (-1);
}

static double	shoot_ray_bottom(t_vec *ray, t_cy *cy, t_point *start)
{
	t_vec	v;
	double	t;
	t_point	poi;

	v = subtract_vecs(cy->bottom, *start);
	t = dot_vecs(v, cy->n_vector) / dot_vecs(*ray, cy->n_vector);
	if (t < 0)
		return (-1);
	poi = add_vecs(*start, scale_vec(*ray, t));
	int len = get_vec_len(subtract_vecs(poi, cy->bottom));
	if (len < cy->radius)
		return (t);
	return (-1);
}

static double	shoot_ray_side(t_vec *ray, t_cy *cy, t_point *start)
{
	t_vec	w;
	t_vec	coefficient;
	double	t;
	double	poi_height;

	w = subtract_vecs(*start, cy->bottom);
	coefficient.x = dot_vecs(*ray, *ray) - pow(dot_vecs(*ray, cy->n_vector), 2);
	coefficient.y = 2 * (dot_vecs(*ray, w) - \
		(dot_vecs(*ray, cy->n_vector) * dot_vecs(w, cy->n_vector)));
	coefficient.z = dot_vecs(w, w) - pow(dot_vecs(w, cy->n_vector), 2) - \
		pow(cy->radius, 2);
	t = get_root(&coefficient);
	if (t < 0) // DARKNESS, -1
		return (t);
	poi_height = dot_vecs(subtract_vecs(add_vecs(*start, scale_vec(*ray, t)), cy->bottom), cy->n_vector);
	if (is_between(0, cy->height, poi_height))
		return (t);
	return (-1);
}

// 0 is top or bottom. 1 is side.
// 밑면, 옆면
// 1. 둘 중 가까운 t를 구함 (get_root 갔다와서 3가지 경우의 수만 존재함.)
// 2. DARKNESS
double	check_root(double *t, t_ptype *type)
{
	if (t[1] == INFINITY) // TOP, BOTTOM, SIDE
		return (t[0]);
	if (t[0] < t[1])
	{
		if (t[0] < 0 && t[1] >= 0)
			return (DARKNESS);
		return (t[0]); // -1 or 양수
	}
	else
	{
		if (t[0] >= 0 && t[1] < 0)
			return (DARKNESS);
		*type = CYLINDER_SIDE;
		return (t[1]); // -1 or 양수
	}
}

double	shoot_ray_cy(t_vec *ray, t_cy *cy, t_point *start, t_ptype *type)
{
	double	t;
	double 	tmin;

	tmin = INFINITY;
	// if (cy->side == TOP || cy->side == TOP_SIDE)
	// {
		t = shoot_ray_top(ray, cy, start);
		if (t < tmin && t >= 0)
		{
			tmin = t;
			*type = CYLINDER_TOP;
		}
	// }
	// if (cy->side == BOTTOM || cy->side == BOTTOM_SIDE)
	// {
		t = shoot_ray_bottom(ray, cy, start);
		if (t < tmin && t >= 0)
		{
			tmin = t;
			*type = CYLINDER_TOP;
		}
	// }
	// if (cy->side == SIDE || cy->side == TOP_SIDE || cy->side == BOTTOM_SIDE)
	// {
		t =shoot_ray_side(ray, cy, start);
		if (t < tmin && t >= 0)
		{
			tmin = t;
			*type = CYLINDER_SIDE;
		}
	// }
	return (tmin);
}

/*
double	shoot_ray_cy(t_vec *ray, t_cy *cy, t_point *start, t_ptype *type)
{
	double	t[2];

	t[0] = INFINITY;
	t[1] = INFINITY;
	if (cy->side == TOP || cy->side == TOP_SIDE)
	{
		t[0] = shoot_ray_top(ray, cy, start);
		*type = CYLINDER_TOP;
	}
	if (cy->side == BOTTOM || cy->side == BOTTOM_SIDE)
	{
		t[0] = shoot_ray_bottom(ray, cy, start);
		*type = CYLINDER_BOTTOM;
	}
	if (cy->side == SIDE || cy->side == TOP_SIDE || cy->side == BOTTOM_SIDE)
	{
		if (t[0] == INFINITY)
		{
			t[0] = shoot_ray_side(ray, cy, start);
			*type = CYLINDER_SIDE;
		}
		else
			t[1] = shoot_ray_side(ray, cy, start); // 근이 2개
	}
	return (check_root(t, type));
}
*/