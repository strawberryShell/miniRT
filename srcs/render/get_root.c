/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_root.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 01:12:08 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/18 16:04:53 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// root(t)의 tmin = 1
// 반환값이 0이면 접점이 없거나 있어도 카메라뷰에서는 보이지 않는다.
double	get_root(double a, double b, double c)
{
	double	root;
	double	root1;
	double	root2;
	double	discriminant;

	if (a == 0)
		exit_with_err("Dividing value by 0 is impossible ", "get_root");
	root = 0;
	discriminant = b * b - 4 * a * c;
	if (discriminant > 0)
	{
		root1 = (-b - sqrt(discriminant)) * 0.5 * (1 / a);
		root2 = (-b + sqrt(discriminant)) * 0.5 * (1 / a);
		if (root1 >= 1 && root2 >= 1)
			root = root1;
		else if (root1 < 1 && root2 >= 1)
			root = root2;
	}
	else if (!discriminant)
		root = -b * 0.5 * (1 / a);
	if (root < 1)
		root = 0;
	return (root);
}
