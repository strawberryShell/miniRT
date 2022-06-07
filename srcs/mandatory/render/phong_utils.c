/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 21:58:43 by jiskim            #+#    #+#             */
/*   Updated: 2022/06/07 18:57:38 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

int	is_shadow(t_poi *poi, t_box *box)
{
	t_obj	*cur;
	t_vec	light;
	double	t;

	cur = box->objs;
	while (cur)
	{
		if (poi->data != cur->data)
		{
			if (cur->type == SPHERE)
				t = shoot_ray_sp(&light, (t_sp *)cur->data, &poi->point, NULL);
			else if (cur->type == PLANE)
				t = shoot_ray_pl(&light, (t_pl *)cur->data, NULL);
			else if (cur->type == CYLINDER)
				t = shoot_ray_cy(&light, (t_cy *)cur->data, &poi->point, NULL);
			else
				t = shoot_ray_cn(&light, (t_cn *)cur->data, &poi->point, NULL);
			if (t >= 0 && t < 1)
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
