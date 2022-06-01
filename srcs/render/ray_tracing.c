/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:20:41 by jiskim            #+#    #+#             */
/*   Updated: 2022/06/01 11:12:06 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		calc_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

double	get_root(t_vec *coeffient)
{
	double	d;
	double	t;

	d = pow(coeffient->y, 2) - 4 * coeffient->x * coeffient->z;
	if (coeffient->x == 0 || d < 0)
		t = -1; // no root
	else
	{
		t = (coeffient->y - sqrt(d)) / (2 * coeffient->x); //근의 공식
		if (t < 0) // behind the camera
		{
			t = (coeffient->y + sqrt(d)) / (2 * coeffient->x);
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
	t_vec	coeffient; //a, b, c

	coeffient.x = pow(vec->x, 2) + pow(vec->y, 2) + pow(vec->z, 2);
	coeffient.y = 2 * (vec->x * sp->center.x + vec->y * sp->center.y + \
		vec->z * sp->center.z);
	coeffient.z = pow(sp->center.x, 2) + pow(sp->center.y, 2) + \
		pow(sp->center.z, 2) - pow(sp->radius, 2);
	return (get_root(&coeffient));
}

int phong_lighting(t_poi *poi, t_box *box)
{
	t_vec	light_vec;
	t_vec	poi_vec;
	double	theta;
	t_color	light;
	t_color color;
	t_color	ambient;
	t_color	diffuse;

	light_vec = normalize_vec(subtract_vecs(box->lights->pos, poi->point));
	poi_vec.x = 0;
	//if (poi->type == SPHERE_GENERAL) // 법선벡터 뿐? 딴것도 있음?
		poi_vec = normalize_vec(subtract_vecs(poi->point, ((t_sp *)(poi->data))->center));
	theta = dot_vecs(light_vec, poi_vec);
	if (theta < 0)
		theta = 0;
	ambient = scale_vec(*box->amb_light, (double)1 / 255);
	diffuse = scale_vec(box->lights->color, (theta / 255) * box->lights->b_ratio);
	light = add_vecs(ambient, diffuse);
	if (light.x > 1)
		light.x = 1;
	if (light.y > 1)
		light.y = 1;
	if (light.z > 1)
		light.z = 1;
	printf("ambient %f %f %f \n", ambient.x , ambient.y, ambient.z);
	printf("diffuse %f %f %f \n", diffuse.x, diffuse.y, diffuse.z);
	printf("light %f %f %f \n", light.x, light.y, light.z);
	color = multiply_vecs(light, ((t_sp *)(poi->data))->color);
	printf("color %f %f %f \n", color.x, color.y, color.z);
	return (calc_color(color.x, color.y, color.z));
	//light vec, normal vec -> 모든것을 구할수잇음
}

/* RGBA? */
int		shoot_ray(t_vec *vec, t_box *box)
{
	t_obj	*cur;
	t_poi	poi;
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
			if (t < closest_t)
			{
				poi.point = scale_vec(*vec, t);
				closest_t = t;
				poi.data = cur->data;
				poi.type = SPHERE_GENERAL; //판단필요함
			}
		}
		cur = cur->next;
	}
	if (closest_t == INFINITY)
		return (0); //black
	return (phong_lighting(&poi, box));
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
