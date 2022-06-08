/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_phong_vecs_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 21:50:22 by jiskim            #+#    #+#             */
/*   Updated: 2022/06/08 17:32:16 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_vec	get_cn_nvec(t_poi *poi, t_cn *cn)
{
	t_vec	normal_vec;
	t_vec	hp;
	double	cos_theta;

	if (poi->type == CONE_BOTTOM)
		normal_vec = cn->n_vector;
	else
	{
		hp = subtract_vecs(poi->point, cn->top);
		if (hp.x == 0 && hp.y == 0 && hp.z == 0)
			return (scale_vec(cn->n_vector, -1));
		cos_theta = cn->height / sqrt(pow(cn->height, 2) + pow(cn->radius, 2));
		normal_vec = normalize_vec(add_vecs(hp, \
			scale_vec(cn->n_vector, -1 * get_vec_len(hp) / cos_theta)));
	}
	return (normal_vec);
}

static t_vec	get_cy_nvec(t_poi *poi, t_cy *cy)
{
	t_vec	normal_vec;
	t_vec	cp;
	t_vec	qc;

	if (poi->type == CYLINDER_TOP)
		normal_vec = cy->n_vector;
	else if (poi->type == CYLINDER_BOTTOM)
		normal_vec = scale_vec(cy->n_vector, -1);
	else
	{
		cp = subtract_vecs(poi->point, cy->bottom);
		qc = scale_vec(cy->n_vector, dot_vecs(cp, cy->n_vector) * -1);
		normal_vec = scale_vec(add_vecs(qc, cp), 1 / cy->radius);
	}
	return (normal_vec);
}

t_phong	get_phong_vecs(t_poi *poi, t_box *box)
{
	t_phong	phong;

	phong.cam_vec = normalize_vec(subtract_vecs(box->cam->pos, poi->point));
	if (poi->type == SPHERE_GENERAL)
		phong.normal_vec = normalize_vec(\
			subtract_vecs(poi->point, ((t_sp *)poi->data)->center));
	else if (poi->type == PLANE_GENERAL)
	{
		if (dot_vecs(phong.cam_vec, ((t_pl *)poi->data)->n_vector) > 0)
			phong.normal_vec = ((t_pl *)poi->data)->n_vector;
		else
			phong.normal_vec = scale_vec(((t_pl *)poi->data)->n_vector, -1);
	}
	else if (poi->type == CYLINDER_TOP || poi->type == CYLINDER_BOTTOM \
			|| poi->type == CYLINDER_SIDE)
		phong.normal_vec = get_cy_nvec(poi, poi->data);
	else
		phong.normal_vec = get_cn_nvec(poi, poi->data);
	phong.light_vec = normalize_vec(\
		subtract_vecs(box->lights->pos, poi->point));
	phong.cos_theta = dot_vecs(phong.light_vec, phong.normal_vec);
	if (phong.cos_theta < 0.0002)
		phong.cos_theta = 0;
	phong.reflect_vec = add_vecs(scale_vec(phong.light_vec, -1), \
		scale_vec(phong.normal_vec, 2 * phong.cos_theta));
	return (phong);
}
