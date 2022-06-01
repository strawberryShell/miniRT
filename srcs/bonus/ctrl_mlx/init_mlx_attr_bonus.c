/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_attr_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:15:05 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/30 10:42:40 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	init_frame(t_img *frame, void *mlx)
{
	frame->img = mlx_new_image(mlx, SCN_WIDTH, SCN_HEIGHT);
	if (!frame->img)
		exit_with_err("Failed to create mlx image", NULL);
	frame->addr = (int *)mlx_get_data_addr(frame->img, &frame->bpp, \
		&frame->line_len, &frame->endian);
	if (!frame->addr)
		exit_with_err("Failed to get mlx data address", NULL);
}

void	init_mlx_attr(t_box *box)
{
	box->mlx = mlx_init();
	box->win = mlx_new_window(box->mlx, SCN_WIDTH, SCN_HEIGHT, "miniRT");
	if (box->mlx == NULL || box->win == NULL)
		exit_with_err("Failed to initialize mlx", NULL);
	init_frame(&box->frame, box->mlx);
}
