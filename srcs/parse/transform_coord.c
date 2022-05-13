/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_coord.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:52:07 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/13 17:44:00 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	void	fill_rotation(double *tr_matrix, t_vec x_axis, t_vec y_axis, t_vec z_axis)
{
	tr_matrix[0] = x_axis.x;
	tr_matrix[1] = y_axis.x;
	tr_matrix[2] = z_axis.x;
	tr_matrix[4] = x_axis.y;
	tr_matrix[5] = y_axis.y;
	tr_matrix[6] = z_axis.y;
	tr_matrix[8] = x_axis.z;
	tr_matrix[9] = y_axis.z;
	tr_matrix[10] = z_axis.z;
	tr_matrix[15] = 1;
}

static	void	fill_xlocation(t_camera camera, double *tr_matrix)
{
	tr_matrix[3] = -(tr_matrix[0] * camera.pos.x + tr_matrix[1] * camera.pos.y + tr_matrix[2] * camera.pos.z);
	tr_matrix[7] = -(tr_matrix[4] * camera.pos.x + tr_matrix[5] * camera.pos.y + tr_matrix[6] * camera.pos.z);
	tr_matrix[11] = -(tr_matrix[8] * camera.pos.x + tr_matrix[9] * camera.pos.y + tr_matrix[10] * camera.pos.z);
}

static	void	fill_tr_matrix(t_camera camera, double *tr_matrix)
{
	t_vec	x_axis;
	t_vec	y_axis;
	t_vec	z_axis;
	t_vec	ran_vec;

	z_axis = scale_vec(camera.n_vector, -1);
	ran_vec = new_vec(0, 1, 0);
	if (!cmp_vec(z_axis, ran_vec) || !cmp_vec(camera.n_vector, ran_vec))
		ran_vec = new_vec(0, 0, 1);
	y_axis = cross_vec(ran_vec, z_axis);
	printf("y axis: (%f, %f, %f)\n", y_axis.x, y_axis.y, y_axis.z);
	x_axis = cross_vec(y_axis, z_axis);
	printf("x axis: (%f, %f, %f)\n", x_axis.x, x_axis.y, x_axis.z);
	fill_rotation(tr_matrix, x_axis, y_axis, z_axis);
	fill_xlocation(camera, tr_matrix);
}

void	transform_coord(t_box *box)
{
	double	*tr_matrix;
	t_obj	*curr;

	tr_matrix = (double *)ft_calloc(16, sizeof(double));
	if (!tr_matrix)
		exit_with_err("Failed to call malloc()", strerror(errno));
	fill_tr_matrix(box->camera, tr_matrix);
	// light -> camera -> objects모두 적용
	box->camera.pos = transform_point(tr_matrix, box->camera.pos);
	box->camera.n_vector = transform_vec(tr_matrix, box->camera.n_vector);
	box->light.pos = transform_point(tr_matrix, box->light.pos);
	curr = box->objs;
	while (curr)
	{
		if (curr->type == SPHERE)
			((t_sp*)(curr->data))->centre = transform_point(tr_matrix, ((t_sp*)(curr->data))->centre);
		else if (curr->type == PLANE)
		{
			((t_pl *)(curr->data))->point = transform_point(tr_matrix, ((t_pl *)(curr->data))->point);
			((t_pl *)(curr->data))->n_vector = transform_vec(tr_matrix, ((t_pl *)(curr->data))->n_vector);
		}
		else if (curr->type == CYLINDER)
		{
			((t_cy *)(curr->data))->point = transfo_vecs(((t_cy *)(curr->data))->point, new_vec(tr_matrix[3], tr_matrix[7], tr_matrix[11]));
			((t_cy *)(curr->data))->n_vector = transform_vec3(tr_matrix, ((t_cy *)(curr->data))->n_vector);		
		}
		curr = curr->next;
	}
}