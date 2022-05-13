/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:05:22 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/13 17:44:01 by sehhong          ###   ########.fr       */
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

double	vec_len(t_vec vec)
{
	double	square;

	square = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	return (sqrt(square));
}

double	dot_vec(t_vec vec1, t_vec vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec	cross_vec(t_vec vec1, t_vec vec2)
{
	t_vec	new_vec;

	new_vec.x = vec1.y * vec2.z - vec1.z * vec2.y;
	new_vec.y = vec1.z * vec2.x - vec1.x * vec2.z;
	new_vec.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (new_vec);
}

t_vec	scale_vec(t_vec vec, double k)
{
	t_vec	new_vec;

	new_vec.x = k * vec.x;
	new_vec.y = k * vec.y;
	new_vec.z = k * vec.z;
	return (new_vec);
}

t_vec	add_vecs(t_vec vec1, t_vec vec2)
{
	t_vec	new_vec;

	new_vec.x = vec1.x + vec2.x;
	new_vec.y = vec1.y + vec2.y;
	new_vec.z = vec1.z + vec2.z;
	return (new_vec);
}

int	cmp_vec(t_vec vec1, t_vec vec2)
{
	if (vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z)
		return (0);
	return (1);
}

t_vec	transform_vec(double *m, t_vec vec)
{
	t_vec	new_vec;
	double	vec_len_rv;

	new_vec.x = m[0] * vec.x + m[1] * vec.y + m[2] * vec.z;
	new_vec.y = m[4] * vec.x + m[5] * vec.y + m[6] * vec.z;
	new_vec.z = m[8] * vec.x + m[9] * vec.y + m[10] * vec.z;
	return (new_vec);
}

t_point	transform_point(double *m, t_point point)
{
	t_point	new_point;

	new_point.x = m[0] * point.x + m[1] * point.y + m[2] * point.z + m[3];
	new_point.y = m[4] * point.x + m[5] * point.y + m[6] * point.z + m[7];
	new_point.z = m[8] * point.x + m[9] * point.y + m[10] * point.z + m[11];
	return (new_point);
}