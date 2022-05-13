/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:31:06 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/13 12:00:05 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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