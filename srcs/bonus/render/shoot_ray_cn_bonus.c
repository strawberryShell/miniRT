/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_ray_cn_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 20:52:02 by sehhong           #+#    #+#             */
/*   Updated: 2022/06/07 22:36:40 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static double	shoot_ray_bottom(t_vec *ray, t_cn *cn, t_point *start)
{
	double	t;
	double	cos_theta;
	t_vec	v;
	t_point	bottom;

	bottom = add_vecs(cn->top, scale_vec(cn->n_vector, cn->height));
	v = subtract_vecs(bottom, *start);
	cos_theta = dot_vecs(*ray, cn->n_vector);
	if (cos_theta == 0)
		return (-1);
	t = dot_vecs(v, cn->n_vector) / cos_theta;
	if (t < 0)
		return (-1);
	if (get_vec_len(subtract_vecs(add_vecs(*start, scale_vec(*ray, t)), \
		bottom)) <= cn->radius)
		return (t);
	return (-1);
}

static	double	find_t_side(t_vec *ray, t_cn *cn, t_point *start)
{
	t_vec	w;
	t_vec	coef;
	double	m;

	w = subtract_vecs(*start, cn->top);
	m = pow(cn->radius / cn->height, 2) + 1;
	coef.x = dot_vecs(*ray, *ray) - \
		m * pow(dot_vecs(*ray, cn->n_vector), 2);
	coef.y = 2 * (dot_vecs(*ray, w) - m * \
		dot_vecs(*ray, cn->n_vector) * dot_vecs(w, cn->n_vector));
	coef.z = dot_vecs(w, w) - m * pow(dot_vecs(w, cn->n_vector), 2);
	return (get_root(&coef));
}

static double	shoot_ray_side(t_vec *ray, t_cn *cn, t_point *start)
{
	double	t;
	double	hq;

	t = find_t_side(ray, cn, start);
	if (t < 0)
		return (-1);
	hq = dot_vecs(subtract_vecs(add_vecs(scale_vec(*ray, t), *start), \
		cn->top), cn->n_vector);
	if (hq >= 0 && hq <= cn->height)
		return (t);
	return (-1);
}

double	shoot_ray_cn(t_vec *ray, t_cn *cn, t_point *start, t_ptype *type)
{
	double	t;
	double	tmin;
	t_ptype	cn_type;

	tmin = INFINITY;
	t = shoot_ray_bottom(ray, cn, start);
	if (t < tmin && t >= 0)
	{
		tmin = t;
		cn_type = CONE_BOTTOM;
	}
	t = shoot_ray_side(ray, cn, start);
	if (t <= tmin && t >= 0)
	{
		tmin = t;
		cn_type = CONE_SIDE;
	}
	if (type)
		*type = cn_type;
	return (tmin);
}
