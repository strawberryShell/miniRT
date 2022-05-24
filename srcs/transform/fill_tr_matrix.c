/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tr_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:23:40 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/24 19:59:21 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	fill_rotation(double *matrix, t_vec x_axis, t_vec y_axis, \
	t_vec z_axis)
{
	matrix[0] = x_axis.x;
	matrix[1] = y_axis.x;
	matrix[2] = z_axis.x;
	matrix[4] = x_axis.y;
	matrix[5] = y_axis.y;
	matrix[6] = z_axis.y;
	matrix[8] = x_axis.z;
	matrix[9] = y_axis.z;
	matrix[10] = z_axis.z;
	matrix[15] = 1;
}

static void	fill_translation(t_cam *cam, double *matrix)
{
	matrix[3] = -(matrix[0] * cam->pos.x + matrix[1] * \
		cam->pos.y + matrix[2] * cam->pos.z);
	matrix[7] = -(matrix[4] * cam->pos.x + matrix[5] * \
		cam->pos.y + matrix[6] * cam->pos.z);
	matrix[11] = -(matrix[8] * cam->pos.x + matrix[9] * \
		cam->pos.y + matrix[10] * cam->pos.z);
}

void	fill_tr_matrix(t_cam *cam, double *matrix)
{
	t_vec	x_axis;
	t_vec	y_axis;
	t_vec	z_axis;
	t_vec	ran_vec;

	z_axis = scale_vec(cam->n_vector, -1);
	ran_vec = new_vec(0, 1, 0);
	if (!cmp_vec(z_axis, ran_vec) || !cmp_vec(cam->n_vector, ran_vec))
		ran_vec = new_vec(0, 0, 1);
	y_axis = cross_vecs(ran_vec, z_axis);
	x_axis = cross_vecs(y_axis, z_axis);
	fill_rotation(matrix, x_axis, y_axis, z_axis);
	fill_translation(cam, matrix);
}
