/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:03:49 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/14 11:04:01 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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