/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_ray_cy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:23:03 by jiskim            #+#    #+#             */
/*   Updated: 2022/06/06 22:26:34 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	shoot_ray_top(t_vec *ray, t_cy *cy, t_point *start)
{
	t_vec	v;
	double	t;
	double	cos_theta;

	v = subtract_vecs(cy->top, *start);
	cos_theta = dot_vecs(*ray, cy->n_vector);
	if (cos_theta == 0)
		return (-1);
	t = dot_vecs(v, cy->n_vector) / cos_theta;
	if (t < 0)
		return (-1);
	if (get_vec_len(subtract_vecs(add_vecs(*start, \
		scale_vec(*ray, t)), cy->top)) <= cy->radius)
		return (t);
	return (-1);
}

static double	shoot_ray_bottom(t_vec *ray, t_cy *cy, t_point *start)
{
	t_vec	v;
	double	t;
	double	cos_theta;

	v = subtract_vecs(cy->bottom, *start);
	cos_theta = dot_vecs(*ray, cy->n_vector);
	if (cos_theta == 0)
		return (-1);
	t = dot_vecs(v, cy->n_vector) / cos_theta;
	if (t < 0)
		return (-1);
	if (get_vec_len(subtract_vecs(add_vecs(*start, scale_vec(*ray, t)), \
		cy->bottom)) <= cy->radius)
		return (t);
	return (-1);
}

static double	shoot_ray_side(t_vec *ray, t_cy *cy, t_point *start)
{
	t_vec	w;
	t_vec	coef;
	double	t;
	double	poi_height;

	w = subtract_vecs(*start, cy->bottom);
	coef.x = dot_vecs(*ray, *ray) - pow(dot_vecs(*ray, cy->n_vector), 2);
	coef.y = 2 * (dot_vecs(*ray, w) - \
		(dot_vecs(*ray, cy->n_vector) * dot_vecs(w, cy->n_vector)));
	coef.z = dot_vecs(w, w) - pow(dot_vecs(w, cy->n_vector), 2) - \
		pow(cy->radius, 2);
	t = get_root(&coef);
	if (t < 0)
		return (-1);
	poi_height = dot_vecs(subtract_vecs(add_vecs(*start, \
		scale_vec(*ray, t)), cy->bottom), cy->n_vector);
	if (is_between(0, cy->height, poi_height))
		return (t);
	return (-1);
}

double	shoot_ray_cy(t_vec *ray, t_cy *cy, t_point *start, t_ptype *type)
{
	double	t;
	double	tmin;
	t_ptype	cy_type;

	tmin = INFINITY;
	cy_type = CYLINDER_TOP;
	t = shoot_ray_top(ray, cy, start);
	if (t < tmin && t >= 0)
		tmin = t;
	t = shoot_ray_bottom(ray, cy, start);
	if (t < tmin && t >= 0)
	{
		tmin = t;
		cy_type = CYLINDER_BOTTOM;
	}
	t = shoot_ray_side(ray, cy, start);
	if (t < tmin && t >= 0)
	{
		tmin = t;
		cy_type = CYLINDER_SIDE;
	}
	if (type)
		*type = cy_type;
	return (tmin);
}
