/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:05:22 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/11 17:15:18 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vec_len(t_vec vec)
{
	double	square;

	square = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	return (sqrt(square));
}

double	vec_dot(t_vec vec1, t_vec vec2)
{
	double	dot;

	dot = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return (dot);
}