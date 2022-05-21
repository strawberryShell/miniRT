/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tr_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:23:40 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/18 16:48:06 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	void	fill_rotation(double *tr_matrix, t_vec x_axis, t_vec y_axis, \
	t_vec z_axis)
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

static	void	fill_translation(t_camera *camera, double *tr_matrix)
{
	tr_matrix[3] = -(tr_matrix[0] * camera->pos.x + tr_matrix[1] * \
		camera->pos.y + tr_matrix[2] * camera->pos.z);
	tr_matrix[7] = -(tr_matrix[4] * camera->pos.x + tr_matrix[5] * \
		camera->pos.y + tr_matrix[6] * camera->pos.z);
	tr_matrix[11] = -(tr_matrix[8] * camera->pos.x + tr_matrix[9] * \
		camera->pos.y + tr_matrix[10] * camera->pos.z);
}

void	fill_tr_matrix(t_camera *camera, double *tr_matrix)
{
	t_vec	x_axis;
	t_vec	y_axis;
	t_vec	z_axis;
	t_vec	ran_vec;

	z_axis = scale_vec(camera->n_vector, -1);
	ran_vec = new_vec(0, 1, 0);
	if (!cmp_vec(z_axis, ran_vec) || !cmp_vec(camera->n_vector, ran_vec))
		ran_vec = new_vec(0, 0, 1);
	y_axis = cross_vecs(ran_vec, z_axis);
	x_axis = cross_vecs(y_axis, z_axis);
	fill_rotation(tr_matrix, x_axis, y_axis, z_axis);
	fill_translation(camera, tr_matrix);
}
