/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:56:53 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/11 22:19:09 by sehhong          ###   ########.fr       */
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