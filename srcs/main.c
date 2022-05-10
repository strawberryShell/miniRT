/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:00:12 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/10 23:35:52 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	exit_with_err(char *err_str, char *err_str2, int exit_code)
{
	ft_putendl_fd(err_str, STDERR_FILENO);
	if (err_str2)
		ft_putendl_fd(err_str2, STDERR_FILENO);
	exit(exit_code);
}

int	main(int argc, char **argv)
{
	t_box	box;

	if (argc != 2)
		exit_with_err("Invalid number of argument", NULL, EXIT_FAILURE);
	read_file(&box, argv[1]);
	// transform_coordinate();
	// box.mlx = mlx_init();
	// box.win = mlx_new_window(box.mlx, SCN_WIDTH, SCN_HEIGHT, "miniRT");
	// 모든 픽셀 채운 뒤, mlx_put_image_to_window()
	// mlx_loop(box.mlx);
	return (0);
}