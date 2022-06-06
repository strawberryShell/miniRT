/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:03:49 by sehhong           #+#    #+#             */
/*   Updated: 2022/06/06 21:14:48 by jiskim           ###   ########.fr       */
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
	sp->center = parse_vector(arr[1], ele, POINT);
	sp->radius = ft_atod(arr[2], ele) * 0.5;
	if (sp->radius < 0)
		exit_with_err("Invalid value of radius : ", ele);
	sp->color = parse_vector(arr[3], ele, COLOR);
	add_obj(box, SPHERE, sp);
}

void	parse_plane(t_box *box, char **arr)
{
	t_pl	*pl;
	char	*ele;

	ele = "plane";
	validate_arr(arr, 4, ele);
	pl = (t_pl *)ft_calloc(1, sizeof(t_pl));
	pl->point = parse_vector(arr[1], ele, POINT);
	pl->n_vector = parse_vector(arr[2], ele, VECTOR);
	pl->color = parse_vector(arr[3], ele, COLOR);
	add_obj(box, PLANE, pl);
}

void	parse_cylinder(t_box *box, char **arr)
{
	t_cy	*cy;
	char	*ele;

	ele = "cylinder";
	validate_arr(arr, 6, ele);
	cy = (t_cy *)ft_calloc(1, sizeof(t_cy));
	cy->bottom = parse_vector(arr[1], ele, POINT);
	cy->n_vector = parse_vector(arr[2], ele, VECTOR);
	cy->radius = ft_atod(arr[3], ele) * 0.5;
	if (cy->radius <= 0)
		exit_with_err("Invalid value of radius : ", ele);
	cy->height = ft_atod(arr[4], ele);
	if (cy->height <= 0)
		exit_with_err("Invalid value of height : ", ele);
	cy->color = parse_vector(arr[5], ele, COLOR);
	cy->top = add_vecs(scale_vec(cy->n_vector, cy->height), cy->bottom);
	add_obj(box, CYLINDER, cy);
}

void	parse_cone(t_box *box, char **arr)
{
	t_cn	*cn;
	char	*ele;

	ele = "cone";
	validate_arr(arr, 6, ele);
	cn = (t_cn *)ft_calloc(1, sizeof(t_cn));
	cn->top = parse_vector(arr[1], ele, POINT);
	cn->n_vector = parse_vector(arr[2], ele, VECTOR);
	cn->radius = ft_atod(arr[3], ele) * 0.5;
	if (cn->radius <= 0)
		exit_with_err("Invalid value of radius : ", ele);
	cn->height = ft_atod(arr[4], ele);
	if (cn->height <= 0)
		exit_with_err("Invalid value of height : ", ele);
	cn->color = parse_vector(arr[5], ele, COLOR);
	add_obj(box, CONE, cn);
}
