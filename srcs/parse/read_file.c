/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:33:38 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/24 18:30:36 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	void	analyze_line(t_box *box, char *line)
{
	char	**arr;

	arr = ft_split(line, ' ');
	if (!arr)
		exit_with_err("Failed to call malloc()", NULL);
	if (!ft_strncmp(arr[0], "A", 2))
		parse_ambient(box, arr);
	else if (!ft_strncmp(arr[0], "L", 2))
		parse_light(box, arr);
	else if (!ft_strncmp(arr[0], "C", 2))
		parse_cam(box, arr);
	else if (!ft_strncmp(arr[0], "sp", 3))
		parse_sphere(box, arr);
	else if (!ft_strncmp(arr[0], "pl", 3))
		parse_plane(box, arr);
	else if (!ft_strncmp(arr[0], "cy", 3))
		parse_cylinder(box, arr);
	else
		exit_with_err("Wrong type identifier was given in the file", NULL);
	free_str_arr(&arr);
	arr = NULL;
}

// 파싱결과 validate하기
static	void	validate_file(t_box *box)
{
	if (!box->cam)
		exit_with_err("Cannot find camera element in the file", NULL);
	if (!box->amb_light)
		exit_with_err("Cannot find ambient lightning element in the file", \
			NULL);
	if (!box->lights)
		exit_with_err("Cannot find light element in the file", NULL);
	if (!box->objs)
		exit_with_err("Cannot find any object element in the file", NULL);
}

void	read_file(t_box *box, char *f_name)
{
	char	*ptr;
	char	*line;
	int		fd;

	ptr = ft_strrchr(f_name, '.');
	if (!ptr || ft_strncmp(ptr + 1, "rt", 3))
		exit_with_err("Invalid format of file", NULL);
	fd = open(f_name, O_RDONLY);
	if (fd == -1)
		exit_with_err("Failed to call open(): ", strerror(errno));
	ft_memset(box, 0, sizeof(t_box));
	// gnl 사용법..?
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (*line)
			analyze_line(box, line);
		free(line);
		line = NULL;
	}
	if (*line)
		analyze_line(box, line);
	if (line)
		free(line);
	line = NULL;
	close(fd);
	validate_file(box);
}
