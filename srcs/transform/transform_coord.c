/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_coord.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:52:07 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/16 18:11:30 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	void	transform_objs(t_box *box, double *tr_matrix)
{
	t_obj	*curr;

	curr = box->objs;
	while (curr)
	{
		if (curr->type == SPHERE)
			((t_sp*)(curr->data))->centre = transform_point(tr_matrix, \
				((t_sp*)(curr->data))->centre);
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

static	int	need_transform(t_camera *camera)
{
	return (!(!camera->pos.x && !camera->pos.y && !camera->pos.z && \
		!camera->n_vector.x && !camera->n_vector.y && camera->n_vector.z == -1));
}

void	transform_coord(t_box *box)
{
	double	*tr_matrix;


	if (!need_transform(box->camera))
		return ;
	tr_matrix = (double *)ft_calloc(16, sizeof(double));
	if (!tr_matrix)
		exit_with_err("Failed to call malloc()", strerror(errno));
	fill_tr_matrix(box->camera, tr_matrix);
	// light -> camera -> objects에 만들어진 변환행렬을 모두 적용
	box->lights->pos = transform_point(tr_matrix, box->lights->pos);
	box->camera->pos = transform_point(tr_matrix, box->camera->pos);
	box->camera->n_vector = transform_vec(tr_matrix, box->camera->n_vector);
	transform_objs(box, tr_matrix);
	// box->top_left의 좌표 구하기
	box->top_left = new_vec(-0.5 * SCN_WIDTH, 0.5 * SCN_HEIGHT, \
		 -(box->camera->foc_len));

}