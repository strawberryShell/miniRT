/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xform_coord.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:52:07 by sehhong           #+#    #+#             */
/*   Updated: 2022/06/06 17:47:05 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	xform_objs(t_box *box, double *matrix)
{
	t_obj	*cur;

	cur = box->objs;
	while (cur)
	{
		if (cur->type == SPHERE)
			((t_sp *)(cur->data))->center = xform_point(matrix, \
				((t_sp *)(cur->data))->center);
		else if (cur->type == PLANE)
		{
			((t_pl *)(cur->data))->point = xform_point(matrix, \
				((t_pl *)(cur->data))->point);
			((t_pl *)(cur->data))->n_vector = normalize_vec(xform_vec(matrix, \
				((t_pl *)(cur->data))->n_vector));
		}
		else if (cur->type == CYLINDER)
		{
			((t_cy *)(cur->data))->top = xform_point(matrix, \
				((t_cy *)(cur->data))->top);
			((t_cy *)(cur->data))->bottom = xform_point(matrix, \
				((t_cy *)(cur->data))->bottom);
			((t_cy *)(cur->data))->n_vector = normalize_vec(xform_vec(matrix, \
				((t_cy *)(cur->data))->n_vector));
		}
		else if (cur->type == CONE)
		{
			((t_cn *)(cur->data))->top = xform_point(matrix, \
				((t_cn *)(cur->data))->top);
			((t_cn *)(cur->data))->n_vector = normalize_vec(xform_vec(matrix, \
				((t_cn *)(cur->data))->n_vector));
		}
		cur = cur->next;
	}
}

static int	need_xform(t_cam *cam)
{
	return (!(!cam->pos.x && !cam->pos.y && !cam->pos.z && \
		!cam->n_vector.x && !cam->n_vector.y && cam->n_vector.z == -1));
}

void	xform_coord(t_box *box)
{
	double	*matrix;

	box->top_left = new_vec(-0.5 * SCN_WIDTH, 0.5 * SCN_HEIGHT, \
		-(box->cam->foc_len));
	if (!need_xform(box->cam))
		return ;
	matrix = (double *)ft_calloc(16, sizeof(double));
	fill_tr_matrix(box->cam, matrix);
	printf("xform matrix:\n");
	printf("%f %f %f %f\n", matrix[0], matrix[1], matrix[2], matrix[3]);
	printf("%f %f %f %f\n", matrix[4], matrix[5], matrix[6], matrix[7]);
	printf("%f %f %f %f\n", matrix[8], matrix[9], matrix[10], matrix[11]);
	printf("%f %f %f %f\n", matrix[12], matrix[13], matrix[14], matrix[15]);
	box->lights->pos = xform_point(matrix, box->lights->pos);
	printf("light pos: (%f %f %f)\n", box->lights->pos.x,box->lights->pos.y, box->lights->pos.z);
	box->cam->pos = xform_point(matrix, box->cam->pos);
	box->cam->n_vector = xform_vec(matrix, box->cam->n_vector);
	xform_objs(box, matrix);
	free(matrix);
	matrix = NULL;
}
