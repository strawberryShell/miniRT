/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_coord_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:52:07 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/31 01:09:22 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	transform_objs(t_box *box, double *matrix)
{
	t_obj	*cur;

	cur = box->objs;
	while (cur)
	{
		if (cur->type == SPHERE)
			((t_sp *)(cur->data))->center = transform_point(matrix, \
				((t_sp *)(cur->data))->center);
		else if (cur->type == PLANE)
		{
			((t_pl *)(cur->data))->point = transform_point(matrix, \
				((t_pl *)(cur->data))->point);
			((t_pl *)(cur->data))->n_vector = normalize_vec(transform_vec(matrix, \
				((t_pl *)(cur->data))->n_vector));
		}
		else if (cur->type == CYLINDER)
		{
			((t_cy *)(cur->data))->point = transform_point(matrix, \
				((t_cy *)(cur->data))->point);
			((t_cy *)(cur->data))->n_vector = normalize_vec(transform_vec(matrix, \
				((t_cy *)(cur->data))->n_vector));
		}
		else if (cur->type == CONE)
		{
			((t_cn *)(cur->data))->point = transform_point(matrix, \
				((t_cn *)(cur->data))->point);
			((t_cn *)(cur->data))->n_vector = normalize_vec(transform_vec(matrix, \
				((t_cn *)(cur->data))->n_vector));
		}
		cur = cur->next;
	}
}

static void	transform_lights(t_box *box, double *matrix)
{
	t_light	*cur;

	cur = box->lights;
	while (cur)
	{
		cur->pos = transform_point(matrix, cur->pos);
		cur = cur->next;
	}
}

static int	need_transform(t_cam *cam)
{
	return (!(!cam->pos.x && !cam->pos.y && !cam->pos.z && \
		!cam->n_vector.x && !cam->n_vector.y && \
		cam->n_vector.z == -1));
}

void	transform_coord(t_box *box)
{
	double	*matrix;

	box->top_left = new_vec(-0.5 * SCN_WIDTH, 0.5 * SCN_HEIGHT, \
		-(box->cam->foc_len));
	if (!need_transform(box->cam))
		return ;
	matrix = (double *)ft_calloc(16, sizeof(double));
	fill_tr_matrix(box->cam, matrix);
	box->cam->pos = transform_point(matrix, box->cam->pos);
	box->cam->n_vector = transform_vec(matrix, box->cam->n_vector);
	transform_lights(box, matrix);
	transform_objs(box, matrix);
	free(matrix);
	matrix = NULL;
}
