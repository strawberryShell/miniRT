/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:00:12 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/14 23:29:43 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


int	main(int argc, char **argv)
{
	t_box	box;

	if (argc != 2)
		exit_with_err("Invalid number of argument", NULL);
	read_file(&box, argv[1]);
	// printf("camera:\ncentre: %f, %f, %f\nn_vector: %f, %f, %f\n", \
	// box.camera.pos.x, box.camera.pos.y, box.camera.pos.z, \
	// box.camera.n_vector.x, box.camera.n_vector.y, box.camera.n_vector.z);
	transform_coord(&box);
	// box.mlx = mlx_init();
	// box.win = mlx_new_window(box.mlx, SCN_WIDTH, SCN_HEIGHT, "miniRT");
	// paint_frame(&box);
	// mlx_put_image_to_window(box.mlx, box.win, box.frame.img, 0, 0);
	// mlx_loop(box.mlx);
	// 할당한 부분 모두 free해주기: box다 free해주기
	// printf("camera:\ncentre: %f, %f, %f\nn_vector: %f, %f, %f\n", \
	// box.camera.pos.x, box.camera.pos.y, box.camera.pos.z, \
	// box.camera.n_vector.x, box.camera.n_vector.y, box.camera.n_vector.z);
	return (0);
}