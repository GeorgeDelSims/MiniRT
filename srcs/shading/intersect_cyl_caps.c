/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cyl_caps.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:05:47 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:05:48 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Checks if ray intersects with top cap of cylider
//  adds t_values to intersection struct if so
static void	intersect_top_cap(t_cylinder *cyl, t_ray ray,
		t_intersect *intersection)
{
	double	t_cap_max;
	double	x;
	double	z;

	if (fabs(ray.direction.y) > EPSILON)
	{
		t_cap_max = (cyl->max - ray.origin.y) / ray.direction.y;
		x = ray.origin.x + t_cap_max * ray.direction.x;
		z = ray.origin.z + t_cap_max * ray.direction.z;
		if ((x * x + z * z) <= (cyl->radius * cyl->radius) && t_cap_max > 0)
		{
			if (t_cap_max < intersection->t_value1)
			{
				intersection->t_value1 = t_cap_max;
				intersection->intersected = true;
			}
			else if (t_cap_max < intersection->t_value2)
			{
				intersection->t_value2 = t_cap_max;
				intersection->intersected = true;
			}
		}
	}
}

// Checks if ray intersects with bottom cap of cylider
// adds t_values to intersection struct if so
static void	intersect_bottom_cap(t_cylinder *cyl, t_ray ray,
		t_intersect *intersection)
{
	double	t_cap_min;
	double	x;
	double	z;

	if (fabs(ray.direction.y) > EPSILON)
	{
		t_cap_min = (cyl->min - ray.origin.y) / ray.direction.y;
		x = ray.origin.x + t_cap_min * ray.direction.x;
		z = ray.origin.z + t_cap_min * ray.direction.z;
		if ((x * x + z * z) <= (cyl->radius * cyl->radius) && t_cap_min > 0)
		{
			if (t_cap_min < intersection->t_value1)
			{
				intersection->t_value1 = t_cap_min;
				intersection->intersected = true;
			}
			else if (t_cap_min < intersection->t_value2)
			{
				intersection->t_value2 = t_cap_min;
				intersection->intersected = true;
			}
		}
	}
}

// tests intersects for both caps of cylinder
void	intersect_caps(t_cylinder *cyl, t_ray ray, t_intersect *intersection)
{
	intersect_top_cap(cyl, ray, intersection);
	intersect_bottom_cap(cyl, ray, intersection);
}
