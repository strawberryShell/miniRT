/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:03:49 by sehhong           #+#    #+#             */
/*   Updated: 2022/06/04 20:48:50 by sehhong          ###   ########.fr       */
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
	//if (get_vec_len(pl->n_vector) != 1)
	//	exit_with_err("Vector is not normalized: ", ele);
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
	//if (get_vec_len(cy->n_vector) != 1)
	//	exit_with_err("Vector is not normalized: ", ele);
	cy->radius = ft_atod(arr[3], ele) * 0.5;
	cy->height = ft_atod(arr[4], ele);
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
	cn->n_vector = normalize_vec(parse_vector(arr[2], ele, VECTOR));
	// cn->n_vector = parse_vector(arr[2], ele, VECTOR);
	//if (get_vec_len(cn->n_vector) != 1)
	//	exit_with_err("Vector is not normalized: ", ele);
	cn->radius = ft_atod(arr[3], ele) * 0.5;
	cn->height = ft_atod(arr[4], ele);
	cn->color = parse_vector(arr[5], ele, COLOR);
	cn->cos_theta = cn->height / sqrt(pow(cn->height, 2) + pow(cn->radius, 2));
	add_obj(box, CONE, cn);
}
