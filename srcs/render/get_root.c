/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_root.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 01:12:08 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/15 13:46:32 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// root(t)의 tmin = 1
// 반환값이 0이면 접점이 없거나 있어도 카메라뷰에서는 보이지 않는다.
double	get_root(double a, double b, double c)
{
	double	root;
	double	discriminant;

	if (a == 0)
		exit_with_err("Dividing value by 0 is impossible", NULL);
	root = 0;
	discriminant = b * b - 4 * a * c;
	if (discriminant >= 0)
		root = (-b + sqrt(discriminant)) * 0.5 * (1 / a);
	if (root < 1)
		root = 0;
	return (root);
}