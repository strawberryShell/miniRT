/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:12:47 by sehhong           #+#    #+#             */
/*   Updated: 2022/06/07 22:36:40 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	exit_with_err(char *err_str, char *err_str2)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(err_str, STDERR_FILENO);
	if (err_str2)
		ft_putstr_fd(err_str2, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

int	is_between(double min, double max, double x)
{
	int	ret;

	ret = 0;
	if (x >= min && x <= max)
		ret = 1;
	return (ret);
}

void	free_str_arr(char ***arr)
{
	int	i;

	i = -1;
	if (*arr)
	{
		while ((*arr)[++i])
		{
			free((*arr)[i]);
			(*arr)[i] = NULL;
		}
		free(*arr);
		*arr = NULL;
	}
}
