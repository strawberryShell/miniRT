/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_ray_cn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 20:52:02 by sehhong           #+#    #+#             */
/*   Updated: 2022/06/04 21:39:20 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	shoot_ray_bottom(t_vec *ray, t_cn *cn, t_point *start)
{
	t_vec	v;
	double	t;
	t_point	poi;
    t_point bottom;

    bottom = add_vecs(cn->top, scale_vec(cn->n_vector, cn->height));
	v = subtract_vecs(bottom, *start);
	t = dot_vecs(v, cn->n_vector) / dot_vecs(*ray, cn->n_vector);
	if (t < 0)
		return (-1);
	poi = add_vecs(*start, scale_vec(*ray, t));
	if (get_vec_len(subtract_vecs(poi, bottom)) < cn->radius)
		return (t);
	return (-1);
}

static double	shoot_ray_side(t_vec *ray, t_cn *cn, t_point *start)
{
	t_vec   w;
    t_vec   coefficient;
    double  t;
    t_vec   cp;

    w = subtract_vecs(*start, cn->top);
    coefficient.x = pow(dot_vecs(*ray, cn->n_vector), 2) - \
        pow(cn->cos_theta, 2);
    coefficient.y = 2 * (dot_vecs(*ray, cn->n_vector) * \
        dot_vecs(w, cn->n_vector) - dot_vecs(*ray, w) * pow(cn->cos_theta, 2));
    coefficient.z = pow(dot_vecs(w, cn->n_vector), 2) - dot_vecs(w, w) * \
        pow(cn->cos_theta, 2);
    t = get_root(&coefficient);
    if (t < 0)
        return (-1);
    cp = subtract_vecs(add_vecs(scale_vec(*ray, t), *start), cn->top);
    if (dot_vecs(normalize_vec(cp), cn->n_vector) > 0 && \
        dot_vecs(cp, cn->n_vector) < cn->height)
        return (t);
	return (-1);
}

double	shoot_ray_cn(t_vec *ray, t_cn *cn, t_point *start, t_ptype *type)
{
	double	t;
	double	tmin;
    t_ptype cn_type;

	tmin = INFINITY;
	t = shoot_ray_bottom(ray, cn, start);
    if (t < tmin && t >= 0)
	{
		tmin = t;
		cn_type = CONE_BOTTOM;
	}
	t = shoot_ray_side(ray, cn, start);
	if (t < tmin && t >= 0)
	{
		tmin = t;
		cn_type = CONE_SIDE;
	}
    if (type)
		*type = cn_type;
	return (tmin);
}