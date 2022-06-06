/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 21:07:15 by jiskim            #+#    #+#             */
/*   Updated: 2022/06/06 21:12:03 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	dot_vecs(t_vec vec1, t_vec vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec	cross_vecs(t_vec vec1, t_vec vec2)
{
	t_vec	new_vec;

	new_vec.x = vec1.y * vec2.z - vec1.z * vec2.y;
	new_vec.y = vec1.z * vec2.x - vec1.x * vec2.z;
	new_vec.z = vec1.x * vec2.y - vec1.y * vec2.x;
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

t_vec	subtract_vecs(t_vec vec1, t_vec vec2)
{
	t_vec	new_vec;

	new_vec.x = vec1.x - vec2.x;
	new_vec.y = vec1.y - vec2.y;
	new_vec.z = vec1.z - vec2.z;
	return (new_vec);
}

t_vec	multiply_vecs(t_vec vec1, t_vec vec2)
{
	t_vec	new_vec;

	new_vec.x = vec1.x * vec2.x;
	new_vec.y = vec1.y * vec2.y;
	new_vec.z = vec1.z * vec2.z;
	return (new_vec);
}
