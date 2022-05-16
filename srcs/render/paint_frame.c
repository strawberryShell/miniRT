/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_frame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:49:38 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/16 11:00:25 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_diff_light(t_box *box, t_poi poi)
{
	t_light	*light;
	t_vec	diff_sum;
	t_vec	light_vec;
	t_vec	norm_vec;
	double	light_amount;
	double	diff_factor;

	diff_sum = new_vec(0, 0, 0);
	light = box->lights;
	while (light)
	{
		if (poi.obj->type == SPHERE)
		{
			// 빛위치 ~ 접점까지의 단위벡터
			light_vec  = normalize_vec(subtract_vecs(light->pos, poi.poi));
			// 법선벡터 구하기
			norm_vec = normalize_vec(subtract_vecs(poi.poi, ((t_sp *)(poi.obj->data))->centre));
			// 둘사이 dot product (음수 제거)
			diff_factor = fmax(dot_vecs(light_vec, norm_vec), 0);
			// 보너스에서는 new_vec대신 light->color를 넣으면 될듯
			add_vecs(diff_sum, scale_vec(new_vec(1, 1, 1), light->b_ratio * diff_factor));
		}
		light = light->next;
	}
	return (diff_sum);
};

t_vec	get_spec_light(t_box *box, t_poi poi)
{
	t_light	*light;
	t_vec	spec_sum;
	t_vec	view_dir;
	t_vec	reflect_dir;

	spec_sum = new_vec(0, 0, 0);
	view_dir = subtract_vecs(box->camera->pos, poi.poi);
	while (light)
	{
		reflect_dir =  
		light = light->next;	
	}
	return (spec_sum);	
}

t_vec	get_obj_color(t_poi poi)
{
	t_otype	type;
	t_vec	color;

	type = poi.obj->type;
	if (type == SPHERE)
		color = ((t_sp *)(poi.obj->data))->color;
	else if (type == PLANE)
		color = ((t_pl *)(poi.obj->data))->color;
	else if (type == CYLINDER)
		color = ((t_cy *)(poi.obj->data))->color;
	return (color);
}

double	get_poi_sphere(t_sp *data, t_vec ray)
{
	double	t;
	t_vec	oc;
	double	r;

	oc = data->centre;
	r = data->radius;
	t = get_root(dot_vecs(ray, ray), -2 * dot_vecs(oc, ray), \
		dot_vecs(oc, oc) - r * r);
	return (t);
}

t_poi	find_closest_poi(t_box *box, t_vec ray)
{
	t_obj	*obj;
	t_poi	poi;
	double	t;

	poi.t = INFINITY;
	poi.obj = NULL;
	obj = box->objs;
	while (obj)
	{
		if (obj->type == SPHERE)
			t = get_poi_sphere((t_sp *)(obj->data), ray);
		if (t >= 1 && t < poi.t)
		{
			poi.t = t;
			poi.poi = scale_vec(ray, t);
			poi.obj = obj;
		}
		obj = obj->next;
	}
	return (poi);
}

void	check_range(t_vec *sum_color)
{
	if (sum_color->x > 1)
		sum_color->x = 1;
	if (sum_color->y > 1)
		sum_color->y = 1;
	if (sum_color->z > 1)
		sum_color->z = 1;
}

int	get_pixel_color(t_box *box, int i, int j)
{
	t_vec	sum;
	t_poi	poi;
	t_vec	obj_color;
	t_vec	ray;

	ray = new_vec(box->top_left.x + i, box->top_left.y - j, box->top_left.z);
	sum = new_vec(0, 0, 0);
	poi = find_closest_poi(box, ray);
	add_vecs(sum, get_diff_light(box, poi));
	add_vecs(sum, get_spec_light(box, poi));
	add_vecs(sum, scale_vec(box->amb_light->color, box->amb_light->b_ratio));
	check_range(&sum);
	obj_color = get_obj_color(poi);
	return (multiply_vec(sum, obj_color));
}

void	paint_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	paint_frame(t_box *box)
{
	int	i;
	int	j;

	box->frame.img = mlx_new_image(box->mlx, SCN_WIDTH, SCN_HEIGHT);
	box->frame.addr = mlx_get_data_addr(box->frame.img, \
		&box->frame.bits_per_pixel, &box->frame.line_length, \
		&box->frame.endian);
	i = 0;
	j = 0;
	while (i < SCN_WIDTH)
	{
		j = 0;
		while (j < SCN_HEIGHT)
		{
			paint_pixel(&(box->frame), i, j, get_pixel_color(box, i, j));
			j++;
		}
		i++;
	}
}