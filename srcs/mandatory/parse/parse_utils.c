/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:11:40 by sehhong           #+#    #+#             */
/*   Updated: 2022/06/08 21:47:20 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	add_value(char c, int *dec_cnt, double *d)
{
	if (c == '.')
	{
		if (*dec_cnt != -1)
			exit_with_err("Number in wrong format", NULL);
		*dec_cnt = 0;
	}
	else
	{
		*d = (10 * (*d)) + (c - '0');
		if (*dec_cnt >= 0)
			(*dec_cnt)++;
	}
}

double	ft_atod(char *str, char *ele)
{
	double	d;
	int		sign;
	int		dec_cnt;

	sign = 1;
	d = 0.0;
	dec_cnt = -1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (*str < '0' || *str > '9')
		exit_with_err("Number in wrong format: ", ele);
	while ((*str >= '0' && *str <= '9') || *str == '.')
	{
		add_value(*str, &dec_cnt, &d);
		str++;
	}
	if (*str || !dec_cnt)
		exit_with_err("Number in wrong format: ", ele);
	while (dec_cnt-- > 0)
		d *= 0.1;
	return (sign * d);
}

void	add_obj(t_box *box, t_otype type, void *obj)
{
	t_obj	*new_obj;

	new_obj = (t_obj *)ft_calloc(1, sizeof(t_obj));
	new_obj->type = type;
	new_obj->data = obj;
	if (box->objs)
		new_obj->next = box->objs;
	box->objs = new_obj;
}

void	validate_arr(char **arr, int info_num, char *ele)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	if (i != info_num)
		exit_with_err("Invalid information was given for ", ele);
}

t_vec	parse_vector(char *str, char *ele, int vec_type)
{
	char	**xyz;
	t_vec	new_vec;

	xyz = ft_split(str, ',');
	validate_arr(xyz, 3, ele);
	new_vec.x = ft_atod(xyz[0], ele);
	new_vec.y = ft_atod(xyz[1], ele);
	new_vec.z = ft_atod(xyz[2], ele);
	if (vec_type == COLOR)
	{
		if (!is_between(0, 255, new_vec.x) || !is_between(0, 255, new_vec.y) \
			|| !is_between(0, 255, new_vec.z))
			exit_with_err("Color value is not in range: ", ele);
	}
	else if (vec_type == VECTOR)
	{
		if (!is_between(-1, 1, new_vec.x) || !is_between(-1, 1, new_vec.y) \
			|| !is_between(-1, 1, new_vec.z))
			exit_with_err("Vector is out of range: ", ele);
		if (new_vec.x == 0 && new_vec.y == 0 && new_vec.z == 0)
			exit_with_err("Vector length is zero: ", ele);
		new_vec = normalize_vec(new_vec);
	}
	free_str_arr(&xyz);
	return (new_vec);
}
