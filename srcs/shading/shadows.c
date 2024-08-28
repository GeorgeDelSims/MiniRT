/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:06:12 by gsims             #+#    #+#             */
/*   Updated: 2024/08/20 11:20:15 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Function checks for given point if it is in shadow or not
bool	is_shadow(t_scene *scene, t_tuple point)
{
	double	distance;
	double	hit;
	t_ray	ray;
	t_tuple	light_vector;

	light_vector = subtr_tuple(scene->light_source.position, point);
	distance = magnitude(light_vector);
	ray = create_ray(point, normalise(light_vector));
	ray.intersection_array = intersect_array(scene, ray);
	hit = get_hit(&ray, scene->object_count);
	free(ray.intersection_array);
	if (hit > 0 && hit < distance && hit < DBL_MAX)
		return (true);
	else
		return (false);
}
