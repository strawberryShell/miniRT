/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tr_matrix_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:23:40 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/31 01:07:33 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	fill_rotation(double *matrix, t_vec x_axis, t_vec y_axis, \
	t_vec z_axis)
{
	matrix[0] = x_axis.x;
	matrix[1] = x_axis.y;
	matrix[2] = x_axis.z;
	matrix[4] = y_axis.x;
	matrix[5] = y_axis.y;
	matrix[6] = y_axis.z;
	matrix[8] = z_axis.x;
	matrix[9] = z_axis.y;
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
	y_axis = normalize_vec(cross_vecs(ran_vec, z_axis));
	x_axis = normalize_vec(cross_vecs(y_axis, z_axis));
	fill_rotation(matrix, x_axis, y_axis, z_axis);
	fill_translation(cam, matrix);
}
