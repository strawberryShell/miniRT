/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:56:06 by jiskim            #+#    #+#             */
/*   Updated: 2022/06/06 21:59:31 by jiskim           ###   ########.fr       */
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
	return (scale_vec(box->lights->color, (ratio / 255) \
		 * box->lights->b_ratio * 0.6));
}

t_vec	calc_diffuse(t_phong *phong, t_box *box)
{
	double	cos_theta;

	cos_theta = phong->cos_theta;
	if (cos_theta < 0)
		cos_theta = 0;
	return (scale_vec(box->lights->color, \
		(cos_theta / 255) * box->lights->b_ratio));
}

int	phong_lighting(t_poi *poi, t_box *box)
{
	t_phong		phong;
	t_color		color;
	t_color		light;
	static int	initial = 0;

	phong = get_phong_vecs(poi, box);
	//TODO 꼭짓점과 카메라가 일직선일 경우 꼭짓점을 통과함
	if (poi->point.x == 0 && poi->point.y == 0)
	{
		printf("poi z is %f\n", poi->point.z);
		printf("nv is %f %f %f\n", phong.normal_vec.x, phong.normal_vec.y, phong.normal_vec.z);
	}
	if (!initial)
	{
		initial = 1;
		if (dot_vecs(phong.cam_vec, phong.normal_vec) <= 0)
			return (DARKNESS);
	}
	light = scale_vec(*box->amb_light, (double)1 / 255);
	if (!is_shadow(poi, box))
		light = add_vecs(add_vecs(calc_diffuse(&phong, box), \
			calc_specular(&phong, box)), light);
	color = multiply_vecs(light, *get_obj_color(poi));
	return (calc_color(color.x, color.y, color.z));
}
