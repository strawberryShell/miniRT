/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:19:30 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/24 15:45:34 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	transform_vec(double *tr_m, t_vec vec)
{
	t_vec	new_vec;

	new_vec.x = tr_m[0] * vec.x + tr_m[1] * vec.y + tr_m[2] * vec.z;
	new_vec.y = tr_m[4] * vec.x + tr_m[5] * vec.y + tr_m[6] * vec.z;
	new_vec.z = tr_m[8] * vec.x + tr_m[9] * vec.y + tr_m[10] * vec.z;
	return (new_vec);
}

t_point	transform_point(double *tr_m, t_point point)
{
	t_point	new_point;

	new_point.x = tr_m[0] * point.x + tr_m[1] * point.y + tr_m[2] * point.z + tr_m[3];
	new_point.y = tr_m[4] * point.x + tr_m[5] * point.y + tr_m[6] * point.z + tr_m[7];
	new_point.z = tr_m[8] * point.x + tr_m[9] * point.y + tr_m[10] * point.z + tr_m[11];
	return (new_point);
}
