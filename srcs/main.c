/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:00:12 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/10 11:02:00 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main()
{
	t_box	box;

	box.mlx = mlx_init();
	box.win = mlx_new_window(box.mlx, SCN_WIDTH, SCN_HEIGHT, "miniRT");
	// 모든 픽셀 채운 뒤, mlx_put_image_to_window()
	mlx_loop(box.mlx);
	return (0);
}