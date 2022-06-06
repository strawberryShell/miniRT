/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:20:41 by jiskim            #+#    #+#             */
/*   Updated: 2022/06/06 22:21:14 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	get_root(t_vec *coef)
{
	double	d;
	double	t;

	d = pow(coef->y, 2) - 4 * coef->x * coef->z;
	if (d < 0)
		t = -1;
	else if (coef->x == 0)
	{
		if (coef->y == 0)
			t = -1;
		else
			t = -(coef->z) / coef->y;
	}
	else
	{
		t = (-coef->y - sqrt(d)) / (2 * coef->x);
		if (t < 0)
		{
			t = (-coef->y + sqrt(d)) / (2 * coef->x);
			if (t < 0)
				t = -1;
		}
	}
	return (t);
}

int	shoot_ray(t_vec *ray, t_box *box)
{
	t_obj	*cur;
	t_poi	poi;
	t_ptype	type;
	double	closest_t;
	double	t;

	cur = box->objs;
	closest_t = INFINITY;
	while (cur != 0)
	{
		t = shoot_ray_obj(cur, ray, &box->cam->pos, &type);
		if (t == 0)
			return (0);
		if (t > 0 && t < closest_t)
		{
			poi.point = scale_vec(*ray, t);
			closest_t = t;
			poi.data = cur->data;
			poi.type = type;
		}
		cur = cur->next;
	}
	if (closest_t == INFINITY)
		return (0);
	return (phong_lighting(&poi, box));
}

void	ray_tracing(t_box *box)
{
	t_point	cur;
	int		color;

	cur = box->top_left;
	color = 0;
	while (box->top_left.y - cur.y < SCN_HEIGHT)
	{
		cur.x = box->top_left.x;
		while (cur.x - box->top_left.x < SCN_WIDTH)
		{
			color = shoot_ray(&cur, box);
			if (color == DARKNESS)
			{
				ft_bzero(box->frame.addr, sizeof(box->frame.addr));
				return ;
			}
			box->frame.addr[((int)(box->top_left.y - cur.y) *\
				box->frame.line_len + (int)(cur.x - box->top_left.x) *\
				box->frame.bpp / 8) / 4] = color;
			cur.x++;
		}
		cur.y--;
	}
}
