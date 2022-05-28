/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:20:41 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/28 22:13:53 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	d is discriminant
	t is distance ratio
	t를 구하는 함수
*/

int		calc_color(int r, int g, int b)
{
	return ((r << 24) | (g << 16) | (b << 8));
}

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
	//printf("coeffient.x: %f ", coeffient.x);
	//printf("coeffient.y: %f ", coeffient.y);
	//printf("coeffient.z: %f\n", coeffient.z);
	d = pow(coeffient.y, 2) - 4 * coeffient.x * coeffient.z;
	if (coeffient.x == 0 || d < 0)
		t = -1; // no root
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
}

/* RGBA? */
int		shoot_ray(t_vec *vec, t_box *box)
{
	t_obj	*cur;
	t_vec	closest;
	t_vec	new;
	double	t;

	cur = box->objs;
	closest = new_vec(-1, -1, -1);
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
			new = scale_vec(*vec, t);
			if (new.x < closest.x) // ㅇㅓ차피 z는 같고 x작으면 y도 작음
				closest = new;
		}
		cur = cur->next;
	}
	if (cmp_vec(closest, new_vec(-1, -1, -1)) == 0)
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
	color = 255;
	px = 0;
	py = 0;
	//printf("line_length	: %d\n", box->frame.line_len);
	//printf("%f %f\n", box->top_left.x, box->top_left.y);
	while (py < SCN_HEIGHT)
	{
		cur.x = box->top_left.x;
		px = 0;
		while (px < SCN_WIDTH)
		{
			color = shoot_ray(&cur, box);
			//if (color != 0)
				//printf("%d , %d\n",i, color);
			//if (cur.y <= box->top_left.y - SCN_HEIGHT / 4)
				//color = 255 << 8;
			box->frame.addr[(py * box->frame.line_len + px * box->frame.bpp / 8) / 4] = color;
			//printf("int  i %d , frame %d\n", i, (py * box->frame.line_len + px * box->frame.bpp / 8) / 4);
			cur.x++;
			px++;
		}
		py++;
		cur.y--;
	}
}
