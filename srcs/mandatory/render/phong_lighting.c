/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:56:06 by jiskim            #+#    #+#             */
/*   Updated: 2022/06/09 11:27:36 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	calc_specular(t_phong *phong, t_box *box)
{
	double	ratio;
	double	cos_theta;

	cos_theta = dot_vecs(phong->cam_vec, phong->reflect_vec);
	if (cos_theta < 0)
		cos_theta = 0;
	ratio = pow(cos_theta, 16);
	return (scale_vec(box->lights->color, (ratio / 255) * \
		box->lights->b_ratio * 0.6));
}

t_vec	calc_diffuse(t_phong *phong, t_box *box)
{
	return (scale_vec(box->lights->color, \
		(phong->cos_theta / 255) * box->lights->b_ratio));
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
	light = scale_vec(*box->amb_light, (double)1 / 255);
	if (phong.cos_theta != 0 && !is_shadow(poi, box))
	{
		light = add_vecs(light, calc_diffuse(&phong, box));
		light = add_vecs(light, calc_specular(&phong, box));
	}
	color = multiply_vecs(light, *get_obj_color(poi));
	return (calc_color(color.x, color.y, color.z));
}
