/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lighting_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:56:06 by jiskim            #+#    #+#             */
/*   Updated: 2022/06/09 11:47:48 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_vec	calc_specular(t_phong *phong, t_light *light)
{
	double	ratio;
	double	cos_theta;

	cos_theta = dot_vecs(phong->cam_vec, phong->reflect_vec);
	if (cos_theta < 0)
		cos_theta = 0;
	ratio = pow(cos_theta, 16);
	return (scale_vec(light->color, (ratio / 255) * light->b_ratio * 0.6));
}

t_vec	calc_diffuse(t_phong *phong, t_light *light)
{
	return (scale_vec(light->color, (phong->cos_theta / 255) * light->b_ratio));
}

t_color	calc_lights_albedo(t_phong *phong, t_poi *poi, t_box *box)
{
	t_color	light;
	t_light	*cur;
	t_vec	n_light_vec;

	light = scale_vec(*box->amb_light, (double)1 / 255);
	cur = box->lights;
	while (cur)
	{
		phong->light_vec = subtract_vecs(cur->pos, poi->point);
		n_light_vec = normalize_vec(phong->light_vec);
		phong->cos_theta = dot_vecs(n_light_vec, phong->normal_vec);
		if (phong->cos_theta < 0.0002)
			phong->cos_theta = 0;
		phong->reflect_vec = add_vecs(scale_vec(n_light_vec, -1), \
			scale_vec(phong->normal_vec, 2 * phong->cos_theta));
		if (phong->cos_theta != 0 && !is_shadow(poi, box, &(phong->light_vec)))
		{
			light = add_vecs(light, calc_diffuse(phong, cur));
			light = add_vecs(light, calc_specular(phong, cur));
		}
		cur = cur->next;
	}
	return (light);
}

int	phong_lighting(t_poi *poi, t_box *box)
{
	t_phong		phong;
	t_color		color;
	t_color		light;
	static int	initial = 0;

	phong = get_phong_vecs(poi, box);
	if (!initial)
	{
		initial = 1;
		if (dot_vecs(phong.cam_vec, phong.normal_vec) <= 0)
			return (DARKNESS);
	}
	light = calc_lights_albedo(&phong, poi, box);
	color = multiply_vecs(light, *get_obj_color(poi));
	return (calc_color(color.x, color.y, color.z));
}
