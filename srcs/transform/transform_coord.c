/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_coord.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:52:07 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/24 17:48:54 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	transform_objs(t_box *box, double *tr_matrix)
{
	t_obj	*curr;

	curr = box->objs;
	while (curr)
	{
		if (curr->type == SPHERE)
			((t_sp *)(curr->data))->center = transform_point(tr_matrix, \
				((t_sp *)(curr->data))->center);
		else if (curr->type == PLANE)
		{
			((t_pl *)(curr->data))->point = transform_point(tr_matrix, \
				((t_pl *)(curr->data))->point);
			((t_pl *)(curr->data))->n_vector = transform_vec(tr_matrix, \
				((t_pl *)(curr->data))->n_vector);
		}
		else if (curr->type == CYLINDER)
		{
			((t_cy *)(curr->data))->point = transform_point(tr_matrix, \
				((t_cy *)(curr->data))->point);
			((t_cy *)(curr->data))->n_vector = transform_vec(tr_matrix, \
				((t_cy *)(curr->data))->n_vector);
		}
		curr = curr->next;
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
	double	*tr_matrix;

	if (!need_transform(box->cam))
	{
		// box->top_left의 좌표 구하기
		box->top_left = new_vec(-0.5 * SCN_WIDTH, 0.5 * SCN_HEIGHT, \
			-(box->cam->foc_len));
		return ;
	}
	tr_matrix = (double *)ft_calloc(16, sizeof(double));
	fill_tr_matrix(box->cam, tr_matrix);
	// light -> cam -> objects에 만들어진 변환행렬을 모두 적용
	box->lights->pos = transform_point(tr_matrix, box->lights->pos);
	box->cam->pos = transform_point(tr_matrix, box->cam->pos);
	box->cam->n_vector = transform_vec(tr_matrix, box->cam->n_vector);
	transform_objs(box, tr_matrix);
	// box->top_left의 좌표 구하기
	box->top_left = new_vec(-0.5 * SCN_WIDTH, 0.5 * SCN_HEIGHT, \
		-(box->cam->foc_len));
}
