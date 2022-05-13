/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:00:12 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/13 13:40:13 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	need_transform(t_camera camera)
{
	return (!(!camera.pos.x && !camera.pos.y && !camera.pos.z && \
		!camera.n_vector.x && !camera.n_vector.y && camera.n_vector.z == -1));
}

int	main(int argc, char **argv)
{
	t_box	box;

	if (argc != 2)
		exit_with_err("Invalid number of argument", NULL);
	read_file(&box, argv[1]);
	printf("camera:\ncentre: %f, %f, %f\nn_vector: %f, %f, %f\n", \
	box.camera.pos.x, box.camera.pos.y, box.camera.pos.z, \
	box.camera.n_vector.x, box.camera.n_vector.y, box.camera.n_vector.z);
	if (need_transform(box.camera))
		transform_coord(&box);
	// box.mlx = mlx_init();
	// box.win = mlx_new_window(box.mlx, SCN_WIDTH, SCN_HEIGHT, "miniRT");
	// 모든 픽셀 채운 뒤, mlx_put_image_to_window()
	// mlx_loop(box.mlx);
	// 할당한 부분 모두 free해주기
	printf("camera:\ncentre: %f, %f, %f\nn_vector: %f, %f, %f\n", \
	box.camera.pos.x, box.camera.pos.y, box.camera.pos.z, \
	box.camera.n_vector.x, box.camera.n_vector.y, box.camera.n_vector.z);
	return (0);
}