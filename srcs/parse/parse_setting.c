/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_setting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:05:41 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/24 17:11:12 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambient(t_box *box, char **arr)
{
	char	*ele;

	ele = "ambient lightning";
	if (box->amb_light)
		exit_with_err(ele, " should be given only once");
	validate_arr(arr, 3, ele);
	box->amb_light = (t_amb *)ft_calloc(1, sizeof(t_amb));
	box->amb_light->b_ratio = ft_atod(arr[1], ele);
	if (!is_between(0, 1, box->amb_light->b_ratio))
		exit_with_err("Invalid value of ", ele);
	box->amb_light->color = parse_vector(arr[2], ele, COLOR);
}

void	parse_light(t_box *box, char **arr)
{
	char	*ele;
	t_light	*light;

	ele = "light";
	if (box->lights)
		exit_with_err(ele, " should be given once");
	validate_arr(arr, 4, ele);
	light = (t_light *)ft_calloc(1, sizeof(t_light));
	light->pos = parse_vector(arr[1], ele, POINT);
	light->b_ratio = ft_atod(arr[2], ele);
	if (!is_between(0, 1, light->b_ratio))
		exit_with_err("Invalid value of ", ele);
	light->color = parse_vector(arr[3], ele, COLOR);
	// 보너스부분: add_light() 추가
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
	//if (get_vec_len(box->cam->n_vector) != 1)
	//	exit_with_err("Vector is not normalized: ", ele);
	fov = ft_atod(arr[3], ele);
	if (!is_between(0, 180, fov))
		exit_with_err("Invalid value of FOV", NULL);
	box->cam->foc_len = 0.5 * SCN_WIDTH * (1 / tan(0.5 * fov * M_PI / 180));
}
