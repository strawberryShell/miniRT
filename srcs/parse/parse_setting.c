/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_setting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:05:41 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/14 11:05:46 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambient(t_box *box, char **arr)
{
	char		*ele;

	ele = "ambient lightning";
	if (box->amb_light.is_filled)
		exit_with_err(ele, " should be given only once");
	validate_arr(arr, 3, ele);
	box->amb_light.b_ratio = ft_atod(arr[1], ele);
	if (!is_between(0, 1, box->amb_light.b_ratio))
		exit_with_err("Invalid value of ", ele);
	box->amb_light.color = parse_color(arr[2], ele);
	box->amb_light.is_filled++;
}

void	parse_light(t_box *box, char **arr)
{
	char		*ele;

	ele = "light";
	if (box->light.is_filled)
		exit_with_err(ele, " should be given once");
	validate_arr(arr, 4, ele);
	box->light.pos = parse_point(arr[1], ele);
	box->light.b_ratio = ft_atod(arr[2], ele);
	if (!is_between(0, 1, box->light.b_ratio))
		exit_with_err("Invalid value of ", ele);
	box->light.color = parse_color(arr[3], ele);
	box->light.is_filled++;
}

void	parse_camera(t_box *box, char **arr)
{
	char		*ele;
	double		fov;

	ele = "camera";
	if (box->camera.is_filled)
		exit_with_err(ele, " should be given once");
	validate_arr(arr, 4, ele);
	box->camera.pos = parse_point(arr[1], ele);
	box->camera.n_vector = parse_vector(arr[2], ele);
	if (vec_len(box->camera.n_vector) != 1)
		exit_with_err("Vector is not normalized: ", ele);
	fov = ft_atod(arr[3], ele);
	if (!is_between(0, 180, fov))
		exit_with_err("Invalid value of FOV", NULL);
	box->camera.foc_len = 0.5 * SCN_WIDTH * (1 / tan(0.5 * fov * M_PI / 180));
	box->camera.is_filled++;
}
