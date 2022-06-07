/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:05:22 by sehhong           #+#    #+#             */
/*   Updated: 2022/06/07 18:48:34 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	new_vec(double x, double y, double z)
{
	t_vec	new_vec;

	new_vec.x = x;
	new_vec.y = y;
	new_vec.z = z;
	return (new_vec);
}

double	get_vec_len(t_vec vec)
{
	double	square;

	square = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	return (sqrt(square));
}

int	cmp_vec(t_vec vec1, t_vec vec2)
{
	if (vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z)
		return (0);
	return (1);
}

t_vec	scale_vec(t_vec vec, double k)
{
	t_vec	new_vec;

	new_vec.x = k * vec.x;
	new_vec.y = k * vec.y;
	new_vec.z = k * vec.z;
	return (new_vec);
}

t_vec	normalize_vec(t_vec vec)
{
	t_vec	new_vec;
	double	vec_len;

	vec_len = get_vec_len(vec);
	if (!vec_len)
		exit_with_err("Dividing value by 0 is not allowed ", NULL);
	new_vec.x = vec.x / vec_len;
	new_vec.y = vec.y / vec_len;
	new_vec.z = vec.z / vec_len;
	return (new_vec);
}
