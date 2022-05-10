/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:33:38 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/11 01:08:26 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	int	ft_isspace(int c)
{
	int	ret;

	ret = 0;
	if (c >= 9 && c <= 13 || c == 32)
		ret = 1;
	return (ret);
}

static	t_type	which_type(char **line)
{
	t_type	type;

	if (!ft_strncmp(*line, "A", 2))
		type = AMBIENT;
	else if (!ft_strncmp(*line, "C", 2))
		type = CAMERA;
	else if (!ft_strncmp(*line, "L", 2))
		type = LIGHT;
	else if (!ft_strncmp(*line, "sp", 3))
		type = SPHERE;
	else if (!ft_strncmp(*line, "pl", 3))
		type = PLANE;
	else if (!ft_strncmp(*line, "cy", 3))
		type = CYLINDER;
	else
		exit_with_err("Wrong type identifier was given", NULL, EXIT_FAILURE);
	return (type);
}

static	void	parse_info(t_box *box, t_type type, char *line)
{
	if (type == AMBIENT || type == LIGHT)
		parse_light(box, type, line);
	else if (type == CAMERA)
		parse_camera(box, line);
	else if (type == SPHERE)
		parse_sphere(box, line);
	else if (type == PLANE)
		parse_plane(box, line);
	else
		parse_cylinder(box, line);
}


static	void	analyze_line(t_box *box, char *line)
{
	t_type	type;

	while (ft_isspace(*line))
		line++;
	// type identifier 정하기
	type = which_type(&line);
	if (type >= AMBIENT && type <= LIGHT)
		line++;
	else
		line += 2;
	while (ft_isspace(*line))
		line++;
	// 각 element의 information 저장
	parse_info(box, type, line);
	//free()??
}

void	read_file(t_box *box, char *f_name)
{
	char	*ptr;
	char	*line;
	int		fd;

	ptr = ft_strrchr(f_name, '.');
	if (!ptr || ft_strncmp(ptr + 1, "rt", 3))
		exit_with_err("Invalid format of file", NULL, EXIT_FAILURE);
	fd = open(f_name, O_RDONLY);
	if (fd == -1)
		exit_with_err("Failed to call open()", strerror(errno), EXIT_FAILURE);
	// gnl 사용법..?
	while (get_next_line(fd, &line) > 0)
		analyze_line(box, line);
	if (*line)
		analyze_line(box, line);
	close(fd);
}