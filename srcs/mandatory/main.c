/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:00:12 by sehhong           #+#    #+#             */
/*   Updated: 2022/06/08 18:02:22 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_box	box;

	if (argc != 2)
		exit_with_err("Invalid number of argument", NULL);
	read_file(&box, argv[1]);
	xform_coord(&box);
	init_mlx_attr(&box);
	ray_tracing(&box);
	mlx_put_image_to_window(box.mlx, box.win, (char *)box.frame.img, 0, 0);
	mlx_key_hook(box.win, press_esc, &box);
	mlx_hook(box.win, CLICK_RED, 0, click_red, &box);
	mlx_loop(box.mlx);
	return (0);
}
