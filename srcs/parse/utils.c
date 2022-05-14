/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:11:40 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/14 11:13:47 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	void	add_value(char c, int *dec_cnt, double *d)
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

// TODO 범위 제한??
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
	if (*str == '.')
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
	if (!new_obj)
		exit_with_err("Failed to call malloc()", NULL);
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
