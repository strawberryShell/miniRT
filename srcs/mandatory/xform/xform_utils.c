/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xform_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:19:30 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/24 19:59:21 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	xform_vec(double *matrix, t_vec vec)
{
	t_vec	new_vec;

	new_vec.x = matrix[0] * vec.x + matrix[1] * vec.y + matrix[2] * vec.z;
	new_vec.y = matrix[4] * vec.x + matrix[5] * vec.y + matrix[6] * vec.z;
	new_vec.z = matrix[8] * vec.x + matrix[9] * vec.y + matrix[10] * vec.z;
	return (new_vec);
}

t_point	xform_point(double *matrix, t_point point)
{
	t_point	new_point;

	new_point.x = matrix[0] * point.x + matrix[1] * point.y + \
		matrix[2] * point.z + matrix[3];
	new_point.y = matrix[4] * point.x + matrix[5] * point.y + \
		matrix[6] * point.z + matrix[7];
	new_point.z = matrix[8] * point.x + matrix[9] * point.y + \
		matrix[10] * point.z + matrix[11];
	return (new_point);
}
