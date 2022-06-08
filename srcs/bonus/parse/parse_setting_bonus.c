/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_setting_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:05:41 by sehhong           #+#    #+#             */
/*   Updated: 2022/06/08 21:42:23 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	parse_ambient(t_box *box, char **arr)
{
	char	*ele;
	double	b_ratio;
	t_color	light;

	ele = "ambient lighting";
	if (box->amb_light)
		exit_with_err(ele, " should be given only once");
	validate_arr(arr, 3, ele);
	box->amb_light = (t_color *)ft_calloc(1, sizeof(t_color));
	b_ratio = ft_atod(arr[1], ele);
	if (!is_between(0, 1, b_ratio))
		exit_with_err("Invalid value of ", ele);
	light = parse_vector(arr[2], ele, COLOR);
	box->amb_light->x = light.x * b_ratio;
	box->amb_light->y = light.y * b_ratio;
	box->amb_light->z = light.z * b_ratio;
}

void	parse_light(t_box *box, char **arr)
{
	char	*ele;
	t_light	*light;

	ele = "light";
	validate_arr(arr, 4, ele);
	light = (t_light *)ft_calloc(1, sizeof(t_light));
	light->pos = parse_vector(arr[1], ele, POINT);
	light->b_ratio = ft_atod(arr[2], ele);
	if (!is_between(0, 1, light->b_ratio))
		exit_with_err("Invalid value of ", ele);
	light->color = parse_vector(arr[3], ele, COLOR);
	if (box->lights)
		light->next = box->lights;
	box->lights = light;
}

void	parse_cam(t_box *box, char **arr)
{
	char		*ele;
	double		fov;

	ele = "camera";
	if (box->cam)
		exit_with_err(ele, " should be given once");
	validate_arr(arr, 4, ele);
	box->cam = (t_cam *)ft_calloc(1, sizeof(t_cam));
	box->cam->pos = parse_vector(arr[1], ele, POINT);
	box->cam->n_vector = parse_vector(arr[2], ele, VECTOR);
	fov = ft_atod(arr[3], ele);
	if (fov >= 180 || fov <= 0)
		exit_with_err("Invalid value of FOV", NULL);
	box->cam->foc_len = 0.5 * SCN_WIDTH * (1 / tan(0.5 * fov * M_PI / 180));
}
