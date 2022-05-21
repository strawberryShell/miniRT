/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:00:12 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/18 17:03:53 by sehhong          ###   ########.fr       */
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
	box.mlx = mlx_init();
	box.win = mlx_new_window(box.mlx, SCN_WIDTH, SCN_HEIGHT, "miniRT");
	mlx_loop(box.mlx);
	// 할당한 부분 모두 free해주기: box다 free해주기
	return (0);
}
