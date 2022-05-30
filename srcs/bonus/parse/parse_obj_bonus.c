/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:03:49 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/30 11:19:58 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

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
	pl->n_vector = normalize_vec(parse_vector(arr[2], ele, VECTOR));
	// pl->n_vector = parse_vector(arr[2], ele, VECTOR);
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
	cy->point = parse_vector(arr[1], ele, POINT);
	cy->n_vector = normalize_vec(parse_vector(arr[2], ele, VECTOR));
	// cy->n_vector = parse_vector(arr[2], ele, VECTOR);
	//if (get_vec_len(cy->n_vector) != 1)
	//	exit_with_err("Vector is not normalized: ", ele);
	cy->radius = ft_atod(arr[3], ele) * 0.5;
	cy->height = ft_atod(arr[4], ele);
	cy->color = parse_vector(arr[5], ele, COLOR);
	add_obj(box, CYLINDER, cy);
}

void	parse_cone(t_box *box, char **arr)
{
	t_cn	*cn;
	char	*ele;

	ele = "cone";
	validate_arr(arr, 6, ele);
	cn = (t_cn *)ft_calloc(1, sizeof(t_cn));
	cn->point = parse_vector(arr[1], ele, POINT);
	cn->n_vector = normalize_vec(parse_vector(arr[2], ele, VECTOR));
	// cn->n_vector = parse_vector(arr[2], ele, VECTOR);
	//if (get_vec_len(cn->n_vector) != 1)
	//	exit_with_err("Vector is not normalized: ", ele);
	cn->radius = ft_atod(arr[3], ele) * 0.5;
	cn->height = ft_atod(arr[4], ele);
	cn->color = parse_vector(arr[5], ele, COLOR);
	add_obj(box, CONE, cn);
}
