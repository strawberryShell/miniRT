/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:00:12 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/28 21:32:22 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_box	box;

	if (argc != 2)
		exit_with_err("Invalid number of argument", NULL);
	read_file(&box, argv[1]);
	transform_coord(&box);
	init_mlx_attr(&box);
	ray_tracing(&box);
	mlx_put_image_to_window(box.mlx, box.win, (char *)box.frame.img, 0, 0);
	mlx_loop(box.mlx);
	// TODO 할당한 부분 모두 free해주기: box 다 free해주기
	return (0);
}
