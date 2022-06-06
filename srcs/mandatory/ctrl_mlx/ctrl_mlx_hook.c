/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_mlx_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:46:11 by sehhong           #+#    #+#             */
/*   Updated: 2022/06/06 21:14:12 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	void	free_lights(t_light *lights)
{
	t_light	*tmp;

	while (lights)
	{
		tmp = lights;
		lights = lights->next;
		free(tmp);
	}
}

static	void	free_objs(t_obj *objs)
{
	t_obj	*tmp;

	while (objs)
	{
		tmp = objs;
		objs = objs->next;
		free(tmp->data);
		free(tmp);
	}
}

static	void	finish_program(t_box *box)
{
	free(box->amb_light);
	free(box->cam);
	free_lights(box->lights);
	free_objs(box->objs);
	mlx_destroy_window(box->mlx, box->win);
	exit(EXIT_SUCCESS);
}

int	press_esc(int key_num, t_box *box)
{
	if (key_num == KEY_ESC)
		finish_program(box);
	return (0);
}

int	click_red(t_box *box)
{
	finish_program(box);
	return (0);
}
