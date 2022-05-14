/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_frame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:49:38 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/14 12:07:47 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	paint_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

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

int	calculate_color(t_box *box)
{

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
			paint_pixel(&(box->frame), i, j, calculate_color());
			// if (if_meet(box, i, j))
			// 	paint_pixel(&(box->frame), i, j, 0x00FFFFFF);
			// else
			// 	paint_pixel(&(box->frame), i, j, 0x0000FF00);
			j++;
		}
		i++;
	}
}