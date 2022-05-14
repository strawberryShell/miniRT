/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 00:54:41 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/14 11:31:53 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	parse_color(char *str, char *ele)
{
	char	**rgb;
	t_color	new_color;

	rgb = ft_split(str, ',');
	validate_arr(rgb, 3, ele);
	new_color.x = ft_atod(rgb[0], ele);
	if (!is_between(0, 255, new_color.x))
		exit_with_err("Color value is not in range: ", ele);
	new_color.y = ft_atod(rgb[0], ele);
	if (!is_between(0, 255, new_color.y))
		exit_with_err("Color value is not in range: ", ele);
	new_color.z = ft_atod(rgb[0], ele);
	if (!is_between(0, 255, new_color.z))
		exit_with_err("Color value is not in range: ", ele);
	free_str_arr(&rgb);
	return (new_color);
}

t_point	parse_point(char *str, char *ele)
{
	char	**xyz;
	t_point	new_point;

	xyz = ft_split(str, ',');
	validate_arr(xyz, 3, ele);
	new_point.x = ft_atod(xyz[0], ele);
	new_point.y = ft_atod(xyz[1], ele);
	new_point.z = ft_atod(xyz[2], ele);
	free_str_arr(&xyz);
	return (new_point);
}

t_vec	parse_vector(char *str, char *ele)
{
	char	**xyz;
	t_vec	new_vec;

	xyz = ft_split(str, ',');
	validate_arr(xyz, 3, ele);
	new_vec.x = ft_atod(xyz[0], ele);
	new_vec.y = ft_atod(xyz[1], ele);
	new_vec.z = ft_atod(xyz[2], ele);
	free_str_arr(&xyz);
	return (new_vec);
}
