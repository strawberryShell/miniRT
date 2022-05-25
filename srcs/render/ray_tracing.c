/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:20:41 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/25 22:20:37 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_intersection(t_poi *poi)
{

}

/*
	d is discriminant
	t is distance ratio
*/
int		shoot_ray_sphere(t_vec *vec, t_sp *sp)
{
	t_vec	coeffient;
	int		t;
	int		d;

	coeffient.x = pow(vec->x, 2) + pow(vec->y, 2) + pow(vec->z, 2);
	coeffient.y = -2 * (vec->x * sp->center.x + vec->y * sp->center.y + \
		vec->z * sp->center.z);
	coeffient.z = pow(sp->center.x, 2) + pow(sp->center.y, 2) + \
		pow(sp->center.z, 2) - pow(sp->radius, 2);
	d = pow(coeffient.y, 2) - 4 * coeffient.x * coeffient.z;
	if (d < 0)
		return (-1); // no root
	else if (d == 0)
		t = coeffient.y / (2 * coeffient.x);
	else
	{
		t = (coeffient.y - sqrt(d)) / (2 * coeffient.x);
		if (t < 0) // behind the camera
		{
			t = (coeffient.y + sqrt(d)) / (2 * coeffient.x);
			if (t > 0)
				return (DARKNESS);
		}
	}
	// TODO t는 벡터 길이비율이고 찐 벡터는 알아서 구해야함 t * (vec) 하면될듯
}

/* RGBA? */
int		shoot_ray(t_vec *vec, t_box *box)
{
	t_obj	*cur;

	cur = box->objs;
	while (cur != 0)
	{
		if (cur->type == SPHERE)
			shoot_ray_sp(vec, cur);
		/**
			else if (cur->type == PLANE)
			shoot_ray_pl(vec, cur);
			else if (cur->type == CYLINDER)
			shoot_ray_cy(vec, cur);
			...
		 *
		 */
		cur = cur->next;
	}
	//phong
}

void	ray_tracing(t_box *box)
{
	t_point	cur;

	cur = box->top_left;
	while (cur.y < box->top_left.y + SCN_HEIGHT)
	{
		cur.x = box->top_left.x;
		while (cur.x < box->top_left.x + SCN_WIDTH)
		{
			shoot_ray(&cur, box);
			cur.x++;
		}
		cur.y++;
	}
}
