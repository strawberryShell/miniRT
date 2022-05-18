/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum_diff_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:10:43 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/18 16:30:06 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	t_vec	get_diff_light(t_light *light, t_poi poi)
{
	t_vec	light_vec;
	t_vec	norm_vec;
	double	diff_factor;

	// 빛위치 ~ 접점까지의 단위벡터
	light_vec = normalize_vec(subtract_vecs(light->pos, poi.poi));
	// 둘사이 dot product (음수 제거)
	norm_vec = normalize_vec(subtract_vecs(poi.poi, \
		((t_sp *)(poi.obj->data))->centre));
	diff_factor = fmax(dot_vecs(light_vec, norm_vec), 0);
	// 보너스에서는 new_vec대신 light->color를 넣으면 될듯
	return (scale_vec(new_vec(1, 1, 1), light->b_ratio * diff_factor));
}

// 한 교점을 기준으로 받는 diffuse light -> 모든 빛으로 부터 받는 diffuse light
t_vec	sum_diff_light(t_box *box, t_poi poi)
{
	t_light	*light;
	t_vec	diff_sum;

	diff_sum = new_vec(0, 0, 0);
	light = box->lights;
	while (light)
	{
		if (poi.obj->type == SPHERE)
			diff_sum = add_vecs(diff_sum, get_diff_light(light, poi));
		light = light->next;
	}
	return (diff_sum);
}
