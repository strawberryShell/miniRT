/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum_spec_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:10:03 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/16 17:39:42 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_spec_light(t_light *light, t_poi poi, t_vec view_dir)
{
	t_vec	reflect_vec;
	t_vec	light_vec;
	t_vec	norm_vec;
	double	spec_factor;

	light_vec = subtract_vecs(light->pos, poi.poi);
	norm_vec = normalize_vec(subtract_vecs(poi.poi, ((t_sp *)(poi.obj->data))->centre));
	reflect_vec = add_vecs(scale_vec(light->pos, -1), scale_vec(view_dir, 2 * dot_vecs(norm_vec, light_vec)));
	spec_factor = pow(dot_vecs(reflect_vec, view_dir) / (get_vec_len(reflect_vec) * get_vec_len(view_dir)), 32) * light->b_ratio;
	// 보너스에서는 new_vec(1, 1, 1) 대신 light->color
	return (scale_vec(new_vec(1, 1, 1), spec_factor));
}

t_vec	sum_spec_light(t_box *box, t_poi poi)
{
	t_light	*light;
	t_vec	spec_sum;
	t_vec	view_dir;

	spec_sum = new_vec(0, 0, 0);
	view_dir = normalize_vec(subtract_vecs(box->camera->pos, poi.poi));
	light = box->lights;
	while (light)
	{
		if (poi.obj->type == SPHERE)
			add_vecs(spec_sum, get_spec_light(light, poi, view_dir));
		light = light->next;	
	}
	return (spec_sum);	
}