/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_frame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:49:38 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/16 20:03:20 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	t_vec	get_obj_color(t_poi poi)
{
	t_otype	type;
	t_vec	color;

	type = poi.obj->type;
	if (type == SPHERE)
		color = ((t_sp *)(poi.obj->data))->color;
	else if (type == PLANE)
		color = ((t_pl *)(poi.obj->data))->color;
	else
		color = ((t_cy *)(poi.obj->data))->color;
	return (color);
}

static	void	check_range(t_vec *sum_color)
{
	if (sum_color->x > 1)
		sum_color->x = 1;
	if (sum_color->y > 1)
		sum_color->y = 1;
	if (sum_color->z > 1)
		sum_color->z = 1;
}

static	t_vec	get_pixel_color(t_box *box, int i, int j)
{
	t_vec	sum;
	t_poi	poi;
	t_vec	obj_color;
	t_vec	ray;

	ray = new_vec(box->top_left.x + i, box->top_left.y - j, box->top_left.z);
	sum = new_vec(0, 0, 0);
	poi = find_closest_poi(box, ray);
	// if (!poi.obj)
	// 	printf("안바뀜!\n");
	// printf("poi.t = %f\n", poi.t);
	add_vecs(sum, sum_diff_light(box, poi));
	add_vecs(sum, sum_spec_light(box, poi));
	add_vecs(sum, scale_vec(box->amb_light->color, box->amb_light->b_ratio));
	check_range(&sum);
	obj_color = get_obj_color(poi);
	return (multiply_vecs(sum, obj_color));
}
// why?
static	void	paint_pixel(t_img *img, int x, int y, t_vec color)
{
	char	*dst;
	int		color_int;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color_int = ((int)color.x << 16 | (int)color.y << 8 | (int)color.z);
	*(unsigned int*)dst = color_int;
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