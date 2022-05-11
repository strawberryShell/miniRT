/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 00:54:41 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/12 00:39:06 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	validate_arr(char **arr, int info_num, char *ele)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	if (i != info_num)
		exit_with_err("Invalid information was given for ", ele);
}

t_color	parse_color(char *str, char *ele)
{
	char	**rgb;
	t_color	new_color;

	rgb = ft_split(str, ',');
	validate_arr(rgb, 3, ele);
	new_color.x = ft_atod(rgb[0], ele);
	if (!is_between(0, 255, new_color.x))
		exit_with_err("Color value is not in range: ", ele);
	new_color.y = ft_atod(rgb[0], ele);
	if (!is_between(0, 255, new_color.y))
		exit_with_err("Color value is not in range: ", ele);
	new_color.z = ft_atod(rgb[0], ele);
	if (!is_between(0, 255, new_color.z))
		exit_with_err("Color value is not in range: ", ele);
	free_str_arr(&rgb);
	return (new_color);
}

t_point	parse_point(char *str, char *ele)
{
	char	**xyz;
	t_point	new_point;

	xyz = ft_split(str, ',');
	validate_arr(xyz, 3, ele);
	new_point.x = ft_atod(xyz[0], ele);
	new_point.y = ft_atod(xyz[1], ele);
	new_point.z = ft_atod(xyz[2], ele);
	free_str_arr(&xyz);
	return (new_point);
}

t_vec	parse_vector(char *str, char *ele)
{
	char	**xyz;
	t_vec	new_vec;

	xyz = ft_split(str, ',');
	validate_arr(xyz, 3, ele);
	new_vec.x = ft_atod(xyz[0], ele);
	new_vec.y = ft_atod(xyz[1], ele);
	new_vec.z = ft_atod(xyz[2], ele);
	free_str_arr(&xyz);
	return (new_vec);
}

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

void	parse_sphere(t_box *box, char **arr)
{
	t_sp	*sp;
	char	*ele;

	ele = "sphere";
	validate_arr(arr, 4, ele);
	sp = (t_sp *)ft_calloc(1, sizeof(t_sp));
	if (!sp)
		exit_with_err("Failed to call malloc()", strerror(errno));
	sp->centre = parse_point(arr[1], ele);
	sp->radius = ft_atod(arr[2], ele) * 0.5;
	sp->color = parse_color(arr[3], ele);
	add_obj(box, SPHERE, sp);
}

void	parse_plane(t_box *box, char **arr)
{
	t_pl	*pl;
	char	*ele;

	ele = "plane";
	validate_arr(arr, 4, ele);
	pl = (t_pl *)ft_calloc(1, sizeof(t_pl));
	if (!pl)
		exit_with_err("Failed to call malloc()", strerror(errno));
	pl->point = parse_point(arr[1], ele);
	pl->n_vector = parse_vector(arr[2], ele);
	if (vec_len(pl->n_vector) != 1)
		exit_with_err("Vector is not normalized: ", ele);
	pl->color = parse_color(arr[3], ele);
	add_obj(box, PLANE, pl);
}

void	parse_cylinder(t_box *box, char **arr)
{
	t_cy	*cy;
	char	*ele;

	ele = "cylinder";
	validate_arr(arr, 6, ele);
	cy = (t_cy *)ft_calloc(1, sizeof(t_cy));
	if (!cy)
		exit_with_err("Failed to call malloc()", strerror(errno));
	cy->point = parse_point(arr[1], ele);
	cy->n_vector = parse_vector(arr[2], ele);
	if (vec_len(cy->n_vector) != 1)
		exit_with_err("Vector is not normalized: ", ele);
	cy->radius = ft_atod(arr[3], ele) * 0.5;
	cy->height = ft_atod(arr[4], ele);
	cy->color = parse_color(arr[5], ele);
	add_obj(box, CYLINDER, cy);
}