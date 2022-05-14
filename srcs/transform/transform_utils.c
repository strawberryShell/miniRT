/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:19:30 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/14 22:30:11 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	transform_vec(double *m, t_vec vec)
{
	t_vec	new_vec;

	new_vec.x = m[0] * vec.x + m[1] * vec.y + m[2] * vec.z;
	new_vec.y = m[4] * vec.x + m[5] * vec.y + m[6] * vec.z;
	new_vec.z = m[8] * vec.x + m[9] * vec.y + m[10] * vec.z;
	return (new_vec);
}

t_vec	transform_point(double *m, t_vec point)
{
	t_vec	new_point;

	new_point.x = m[0] * point.x + m[1] * point.y + m[2] * point.z + m[3];
	new_point.y = m[4] * point.x + m[5] * point.y + m[6] * point.z + m[7];
	new_point.z = m[8] * point.x + m[9] * point.y + m[10] * point.z + m[11];
	return (new_point);
}