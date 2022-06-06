/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:56:06 by jiskim            #+#    #+#             */
/*   Updated: 2022/06/06 17:39:21 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		calc_color(int r, int g, int b)
{
	if (r > 255)
		r = 255;
	else if (r < 0)
		r = 0;
	if (g > 255)
		g = 255;
	else if (g < 0)
		g = 0;
	if (b > 255)
		b = 255;
	else if (b < 0)
		b = 0;
	return ((r << 16) | (g << 8) | b);
}

t_vec	calc_specular(t_phong *phong, t_box *box)
{
	double	ratio;
	double	cos_theta;

	cos_theta = dot_vecs(phong->cam_vec, phong->reflect_vec);
	if (cos_theta < 0)
		cos_theta = 0;
	ratio = pow(cos_theta, 16);
	return (scale_vec(box->lights->color, (ratio / 255) \
		 * box->lights->b_ratio * 0.6));
}

t_vec calc_diffuse(t_phong *phong, t_box *box)
{
	double	cos_theta;

	cos_theta = phong->cos_theta;
	if (cos_theta < 0)
		cos_theta = 0;
	return (scale_vec(box->lights->color, \
		(cos_theta / 255) * box->lights->b_ratio));
}

t_vec	get_cn_nvec(t_poi *poi, t_cn *cn)
{
	t_vec	normal_vec;
	t_vec	hp;
	double	cos_theta;

	if (poi->type == CONE_BOTTOM)
		normal_vec = cn->n_vector;
	else
	{
		hp = subtract_vecs(poi->point, cn->top);
		cos_theta = cn->height / sqrt(pow(cn->height, 2) + pow(cn->radius, 2));
		normal_vec = normalize_vec(add_vecs(hp, \
			scale_vec(cn->n_vector, -1 * get_vec_len(hp) / cos_theta)));
	}
	return (normal_vec);
}

t_vec	get_cy_nvec(t_poi *poi, t_cy *cy)
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
	phong.reflect_vec = add_vecs(scale_vec(phong.light_vec, -1), \
		scale_vec(phong.normal_vec, 2 * phong.cos_theta));
	return (phong);
}

int	is_shadow(t_poi *poi, t_box *box)
{
	t_obj	*cur;
	t_vec	light_vec;
	double	t;

	cur = box->objs;
	t = 0;
	while (cur)
	{
		if (poi->data != cur->data)
		{
			light_vec = subtract_vecs(box->lights->pos, poi->point);
			if (cur->type == SPHERE)
				t = shoot_ray_sp(&light_vec, (t_sp *)cur->data, &poi->point, NULL);
			else if (cur->type == PLANE)
				t = shoot_ray_pl(&light_vec, (t_pl *)cur->data, NULL);
			else if (cur->type == CYLINDER)
				t = shoot_ray_cy(&light_vec, (t_cy *)cur->data, &poi->point, NULL);
			else
				t = shoot_ray_cn(&light_vec, (t_cn *)cur->data, &poi->point, NULL);
			if (t > 0 && t < 1)
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}

int	is_darkness(t_phong *phong)
{
	double res = dot_vecs(phong->cam_vec, phong->normal_vec);
	printf("cos is %f\n", res);
	if (dot_vecs(phong->cam_vec, phong->normal_vec) <= 0)
		return (1);
	return (0);
}

int phong_lighting(t_poi *poi, t_box *box)
{
	t_phong	phong;
	t_color	obj_color;
	t_color color;
	t_color	light;
	static int	initial = 0;

	phong = get_phong_vecs(poi, box);
	if (!initial)
	{
		initial = 1;
		if (is_darkness(&phong))
		{
			printf("어두메다크니스\n");
			return (DARKNESS);
		}
	}
	light = scale_vec(*box->amb_light, (double)1 / 255);
	if (!is_shadow(poi, box))
		light = add_vecs(add_vecs(calc_diffuse(&phong, box), \
			calc_specular(&phong, box)), light);
	if (poi->type == SPHERE_GENERAL)
		obj_color = ((t_sp *)poi->data)->color;
	else if (poi->type == PLANE_GENERAL)
		obj_color = ((t_pl *)poi->data)->color;
	else if (poi->type == CYLINDER_TOP || poi->type == CYLINDER_BOTTOM \
		|| poi->type == CYLINDER_SIDE)
		obj_color = ((t_cy *)poi->data)->color;
	else
		obj_color = ((t_cn *)poi->data)->color;
	color = multiply_vecs(light, obj_color);
	return (calc_color(color.x, color.y, color.z));
}
