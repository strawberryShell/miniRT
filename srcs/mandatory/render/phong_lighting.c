/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:56:06 by jiskim            #+#    #+#             */
/*   Updated: 2022/06/01 18:14:16 by jiskim           ###   ########.fr       */
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

t_phong	get_phong_vecs(t_poi *poi, t_box *box)
{
	t_phong	phong;

	phong.light_vec = normalize_vec(\
		subtract_vecs(box->lights->pos, poi->point));
	phong.normal_vec = new_vec(0, 0, 0);
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
	phong.cos_theta = dot_vecs(phong.light_vec, phong.normal_vec);
	phong.reflect_vec = add_vecs(scale_vec(phong.light_vec, -1), \
		scale_vec(phong.normal_vec, 2 * phong.cos_theta));
	return (phong);
}

int phong_lighting(t_poi *poi, t_box *box)
{
	t_phong	phong;
	t_color	obj_color;
	t_color color;
	t_color	light;

	phong = get_phong_vecs(poi, box);
	//light = add_vecs(scale_vec(*box->amb_light, (double)1 / 255), \
		//calc_diffuse(&phong, box));
	light = add_vecs(add_vecs(scale_vec(*box->amb_light, (double)1 / 255), \
		calc_diffuse(&phong, box)), calc_specular(&phong, box));
	obj_color = new_vec(0, 0, 0);
	if (poi->type == SPHERE_GENERAL)
		obj_color = ((t_sp *)poi->data)->color;
	else if (poi->type == PLANE_GENERAL)
		obj_color = ((t_pl *)poi->data)->color;
	color = multiply_vecs(light, obj_color);
	return (calc_color(color.x, color.y, color.z));
}
