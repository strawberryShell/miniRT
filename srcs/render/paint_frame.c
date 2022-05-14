/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_frame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:49:38 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/15 00:48:04 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	if_meet(t_box *box, int x, int y)
{
	t_vec	ray;
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	d;

	oc = new_vec(0, 0, -900);
	ray = new_vec(box->top_left.x + x, box->top_left.y -y, box->top_left.z);
	a = dot(ray, ray);
	b = dot(scale_vec(oc, -2), ray);
	c = dot(oc, oc) - 90000;
	d = b*b - 4 * a * c;
	return (d >= 0); 
}

t_vec	get_diffuse_light()
{};

t_vec	get_specular_light()
{

}

t_vec	get_obj_color(t_obj *obj)
{
	t_otype	type;
	t_vec	color;

	type = obj->type;
	if (type == SPHERE)
		color = ((t_sp *)(obj->data))->color;
	else if (type == PLANE)
		color = ((t_pl *)(obj->data))->color;
	else if (type == CYLINDER)
		color = ((t_cy *)(obj->data))->color;
	return (color);
}

t_obj	get_closest_obj(t_box *box, t_vec ray)
{
	t_obj	*obj;

	obj = box->objs;
	while (obj)
	{
		if ()
		obj = obj->next;
	}
	return (obj);
}

int	calculate_pixel_color(t_box *box, int i, int j)
{
	t_vec	sum;
	t_obj	*obj;
	t_vec	obj_color;
	t_vec	ray;

	ray = new_vec(box->top_left.x + i, box->top_left.y - j, box->top_left.z);
	sum = new_vec(0, 0, 0);
	// 어떤 오브젝트가 빛을 받는지 찾기
	obj = get_closest_obj(box, ray);
	// diffuse 빛
	add_vecs(sum, get_diffuse_light());
	// specular 빛
	add_vecs(sum, get_specular_light());
	// ambient 빛
	add_vecs(sum, scale_vec(box->amb_light->color, box->amb_light->b_ratio));
	// 빛 값 범위 확인
	obj_color = get_obj_color(obj);
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
			paint_pixel(&(box->frame), i, j, calculate_pixel_color());
			j++;
		}
		i++;
	}
}