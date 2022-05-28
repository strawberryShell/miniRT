/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:20:41 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/28 00:41:16 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_intersection(t_poi *poi)
{

}

/*
	d is discriminant
	t is distance ratio
	t를 구하는 함수
*/
double	shoot_ray_sphere(t_vec *vec, t_sp *sp)
{
	t_vec	coeffient;
	double		t;
	double		d;

	coeffient.x = pow(vec->x, 2) + pow(vec->y, 2) + pow(vec->z, 2);
	coeffient.y = -2 * (vec->x * sp->center.x + vec->y * sp->center.y + \
		vec->z * sp->center.z);
	coeffient.z = pow(sp->center.x, 2) + pow(sp->center.y, 2) + \
		pow(sp->center.z, 2) - pow(sp->radius, 2);
	d = pow(coeffient.y, 2) - 4 * coeffient.x * coeffient.z;
	if (d < 0)
		t = -1; // no root
	else if (d == 0)
		t = coeffient.y / (2 * coeffient.x);
	else
	{
		t = (coeffient.y - sqrt(d)) / (2 * coeffient.x);
		if (t < 0) // behind the camera
		{
			t = (coeffient.y + sqrt(d)) / (2 * coeffient.x);
			if (t > 0) // 도형 중간에 카메라가 있으므로 화면 전체가 black
				t = DARKNESS;
			else // 얘도 보이면 안됨 - 루트 없는 취급
				t = -1;
		}
	}
	return (t);
	// TODO t는 벡터 길이비율이고 찐 벡터는 알아서 구해야함 t * (vec) 하면될듯
}

/* RGBA? */
int		shoot_ray(t_vec *vec, t_box *box)
{
	t_obj	*cur;
	t_vec	closest;
	t_vec	new;
	double	t;

	cur = box->objs;
	closest = new_vec(0, 0, 0);
	while (cur != 0)
	{
		if (cur->type == SPHERE)
			t = shoot_ray_sp(vec, cur);
		/**
			else if (cur->type == PLANE)
			shoot_ray_pl(vec, cur);
			else if (cur->type == CYLINDER)
			shoot_ray_cy(vec, cur);
			...
		 *
		 */
		// 이전에 구한 벡터와 비교
		if (t == DARKNESS)
			return (DARKNESS);
		new = scale_vec(*vec, t);
		if (cmp_vec(new, closest) < 0)
			closest = new;
		cur = cur->next;
	}
	// closest로 검사
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
