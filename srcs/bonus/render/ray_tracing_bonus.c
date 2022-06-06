/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:20:41 by jiskim            #+#    #+#             */
/*   Updated: 2022/06/06 15:44:23 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int		calc_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

double	get_root(t_vec *coef)
{
	double	d;
	double	t;

	d = pow(coef->y, 2) - 4 * coef->x * coef->z;
	if (coef->x == 0 || d < 0)
		t = -1; // no root
	else
	{
		t = (coef->y - sqrt(d)) / (2 * coef->x); //근의 공식
		if (t < 0) // behind the camera
		{
			t = (coef->y + sqrt(d)) / (2 * coef->x);
			if (t > 0) // 도형 중간에 카메라가 있으므로 화면 전체가 black
				t = DARKNESS;
			else // 얘도 보이면 안됨 - 루트 없는 취급
				t = -1;
		}
	}
	return (t);
}

double	shoot_ray_sphere(t_vec *vec, t_sp *sp)
{
	t_vec	coef; //a, b, c

	coef.x = pow(vec->x, 2) + pow(vec->y, 2) + pow(vec->z, 2);
	coef.y = 2 * (vec->x * sp->center.x + vec->y * sp->center.y + \
		vec->z * sp->center.z);
	coef.z = pow(sp->center.x, 2) + pow(sp->center.y, 2) + \
		pow(sp->center.z, 2) - pow(sp->radius, 2);
	return (get_root(&coef));
}

int		shoot_ray(t_vec *vec, t_box *box)
{
	t_obj	*cur;
	t_vec	poi;
	double	closest_t;
	double	t;

	cur = box->objs;
	closest_t = INFINITY;
	while (cur != 0)
	{
		if (cur->type == SPHERE)
			t = shoot_ray_sphere(vec, (t_sp *)cur->data);
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
		if (t >= 0)
		{
			if (t < closest_t) // ㅇㅓ차피 z는 같고 x작으면 y도 작음
			{
				poi = scale_vec(*vec, t);
				closest_t = t;
			}
		}
		cur = cur->next;
	}
	if (closest_t == INFINITY)
		return (0); //black
	return (calc_color(box->amb_light->x, box->amb_light->y, box->amb_light->z));
	// closest로 검사
	//phong

}

void	ray_tracing(t_box *box)
{
	t_point	cur;
	int		color;
	int		px;
	int		py;

	cur = box->top_left;
	color = 0;
	px = 0;
	py = 0;
	while (py < SCN_HEIGHT)
	{
		cur.x = box->top_left.x;
		px = 0;
		while (px < SCN_WIDTH)
		{
			color = shoot_ray(&cur, box);
			box->frame.addr[(py * box->frame.line_len + px * box->frame.bpp / 8) / 4] = color;
			cur.x++;
			px++;
		}
		py++;
		cur.y--;
	}
}
