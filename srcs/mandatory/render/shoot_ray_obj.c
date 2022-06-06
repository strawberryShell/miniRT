/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_ray_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:20:03 by jiskim            #+#    #+#             */
/*   Updated: 2022/06/06 22:20:11 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	shoot_ray_sp(t_vec *ray, t_sp *sp, t_point *start, t_ptype *type)
{
	t_vec	coef;
	t_vec	center_start;

	if (type)
		*type = SPHERE_GENERAL;
	center_start = subtract_vecs(*start, sp->center);
	coef.x = dot_vecs(*ray, *ray);
	coef.y = 2 * dot_vecs(center_start, *ray);
	coef.z = dot_vecs(center_start, center_start) - pow(sp->radius, 2);
	return (get_root(&coef));
}

double	shoot_ray_pl(t_vec *ray, t_pl *pl, t_ptype *type)
{
	double	scalar;

	if (type)
		*type = PLANE_GENERAL;
	scalar = dot_vecs(*ray, pl->n_vector);
	if (scalar == 0)
		return (0);
	return (dot_vecs(pl->point, pl->n_vector) / scalar);
}

double	shoot_ray_obj(t_obj *obj, t_vec *ray, t_vec *cam_pos, t_ptype *type)
{
	double	t;

	if (obj->type == SPHERE)
		t = shoot_ray_sp(ray, (t_sp *)obj->data, cam_pos, type);
	else if (obj->type == PLANE)
		t = shoot_ray_pl(ray, (t_pl *)obj->data, type);
	else if (obj->type == CYLINDER)
		t = shoot_ray_cy(ray, (t_cy *)obj->data, cam_pos, type);
	else
		t = shoot_ray_cn(ray, (t_cn *)obj->data, cam_pos, type);
	return (t);
}
