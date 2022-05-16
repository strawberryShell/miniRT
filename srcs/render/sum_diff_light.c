/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum_diff_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:10:43 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/16 17:35:49 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// 한 교점을 기준으로 받는 diffuse light -> 모든 빛으로 부터 받는 diffuse light
t_vec	sum_diff_light(t_box *box, t_poi poi)
{
	t_light	*light;
	t_vec	diff_sum;
	t_vec	light_vec;
	t_vec	norm_vec;
	double	diff_factor;

	diff_sum = new_vec(0, 0, 0);
	light = box->lights;
	while (light)
	{
		if (poi.obj->type == SPHERE)
		{
			// 빛위치 ~ 접점까지의 단위벡터
			light_vec  = normalize_vec(subtract_vecs(light->pos, poi.poi));
			// 법선벡터 구하기
			norm_vec = normalize_vec(subtract_vecs(poi.poi, ((t_sp *)(poi.obj->data))->centre));
			// 둘사이 dot product (음수 제거)
			diff_factor = fmax(dot_vecs(light_vec, norm_vec), 0);
			// 보너스에서는 new_vec대신 light->color를 넣으면 될듯
			add_vecs(diff_sum, scale_vec(new_vec(1, 1, 1), light->b_ratio * diff_factor));
		}
		light = light->next;
	}
	return (diff_sum);
};