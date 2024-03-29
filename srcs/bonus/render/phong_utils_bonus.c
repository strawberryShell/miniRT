/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 21:58:43 by jiskim            #+#    #+#             */
/*   Updated: 2022/06/08 19:08:24 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	calc_color(int r, int g, int b)
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

int	is_shadow(t_poi *poi, t_box *box, t_vec *light_vec)
{
	t_obj	*cur;
	double	t;

	cur = box->objs;
	while (cur)
	{
		if (poi->data != cur->data)
		{
			if (cur->type == SPHERE)
				t = shoot_ray_sp(light_vec, (t_sp *)cur->data, \
					&poi->point, NULL);
			else if (cur->type == PLANE)
				t = shoot_ray_pl(light_vec, (t_pl *)cur->data, NULL);
			else if (cur->type == CYLINDER)
				t = shoot_ray_cy(light_vec, (t_cy *)cur->data, \
					&poi->point, NULL);
			else
				t = shoot_ray_cn(light_vec, (t_cn *)cur->data, \
					&poi->point, NULL);
			if (t > 0.000002 && t < 0.999998)
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}

t_color	*get_obj_color(t_poi *poi)
{
	if (poi->type == SPHERE_GENERAL)
		return (&((t_sp *)poi->data)->color);
	else if (poi->type == PLANE_GENERAL)
		return (&((t_pl *)poi->data)->color);
	else if (poi->type == CYLINDER_TOP || poi->type == CYLINDER_BOTTOM \
			|| poi->type == CYLINDER_SIDE)
		return (&((t_cy *)poi->data)->color);
	else
		return (&((t_cn *)poi->data)->color);
}
